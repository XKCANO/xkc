#include "stdint.h"

#define EEPROM_MAGIC        0x55AA55AA
#define EEPROM_SIZE_FAC     0xFAC0
#define EEPROM_SIZE_FCC     0xFCC0
#define EEPROM_OFFSET_CRC   8
#define EEPROM_OFFSET_MAGIC 12

typedef struct {
    uint8_t state;
    uint8_t flags1;
    uint8_t write_step;
    uint8_t init_done;
    uint32_t work_addr;
    uint32_t backup_addr;
} EEPROM_Control_TypeDef;

extern EEPROM_Control_TypeDef EEPROM_Ctrl;

extern uint32_t *eeprom_data_fac;
extern uint32_t *eeprom_data_fcc;
extern uint32_t Smoke_Config_20000808[64];
extern uint32_t Smoke_Curve_20000848[64];
extern uint32_t Hardware_ID[3];

extern uint32_t fe_calculate_crc(unsigned char *p, unsigned char l);

void copy_eeprom_data(uint32_t src, uint32_t dst, uint32_t len);
void reset_default_data(void);
void EEPROM_write_data(uint32_t addr, uint32_t size, uint32_t *buf);
uint32_t EEPROM_read_data(uint32_t addr, uint32_t size, uint32_t *buf);

static uint8_t validate_eeprom_block(uint32_t *block, uint32_t size)
{
    uint32_t magic;
    uint32_t crc_stored;
    uint32_t crc_calc;

    magic = block[EEPROM_OFFSET_MAGIC / 4];

    if (magic != EEPROM_MAGIC)
    {
        return 0;
    }

    crc_stored = block[EEPROM_OFFSET_CRC / 4];

    crc_calc = fe_calculate_crc((unsigned char *)block, (unsigned char)(size >> 1));

    if (crc_calc == 0)
    {
        return 0;
    }

    if (crc_calc != crc_stored)
    {
        return 0;
    }

    return 1;
}

static void load_eeprom_data(uint32_t *block, uint32_t size, uint8_t is_backup)
{
    uint32_t crc_val;

    copy_eeprom_data((uint32_t)(size >> 1), (uint32_t)Smoke_Config_20000808, size);

    crc_val = fe_calculate_crc((unsigned char *)Smoke_Config_20000808, 0xC8);

    if (crc_val != block[EEPROM_OFFSET_CRC / 4])
    {
        if (!is_backup)
        {
            reset_default_data();
            return;
        }
    }

    EEPROM_Ctrl.flags1 |= (is_backup ? 0x02 : 0x01);
    EEPROM_Ctrl.init_done = 1;
}

void fe_smoke_read_eeprom_data(void)
{
    uint32_t magic_fac;
    uint32_t magic_fcc;

    magic_fac = eeprom_data_fac[EEPROM_OFFSET_MAGIC / 4];
    magic_fcc = eeprom_data_fcc[EEPROM_OFFSET_MAGIC / 4];

    if (magic_fac == EEPROM_MAGIC)
    {
        if (validate_eeprom_block(eeprom_data_fac, 0xFAC0))
        {
            load_eeprom_data(eeprom_data_fac, 0xFAC0, 0);

            if (Smoke_Curve_20000848[0x12] == eeprom_data_fcc[EEPROM_OFFSET_CRC / 4])
            {
                EEPROM_Ctrl.init_done = 1;
            }
            else
            {
                EEPROM_Ctrl.flags1 |= 0x02;
                EEPROM_Ctrl.init_done = 1;
            }
        }
        else
        {
            if (validate_eeprom_block(eeprom_data_fcc, 0xFCC0))
            {
                load_eeprom_data(eeprom_data_fcc, 0xFCC0, 1);
            }
            else
            {
                reset_default_data();
            }
        }
    }
    else
    {
        if (validate_eeprom_block(eeprom_data_fcc, 0xFCC0))
        {
            load_eeprom_data(eeprom_data_fcc, 0xFCC0, 1);
        }
        else
        {
            reset_default_data();
        }
    }

    Hardware_ID[0] = *(volatile uint32_t *)0x4001F030;
    Hardware_ID[1] = *(volatile uint32_t *)0x4001F034;
    Hardware_ID[2] = *(volatile uint32_t *)0x4001F038;

    EEPROM_Ctrl.state |= 0x01;
}

static void eeprom_write_stage1(void)
{
    uint32_t crc_val;

    crc_val = fe_calculate_crc((unsigned char *)Smoke_Config_20000808, 0xC8);

    Smoke_Curve_20000848[0x48] = crc_val;
    Smoke_Curve_20000848[0x4C] = EEPROM_MAGIC;

    if ((EEPROM_Ctrl.flags1 & 0x80) != 0)
    {
        EEPROM_Ctrl.write_step += 2;
    }
    else
    {
        EEPROM_Ctrl.write_step += 1;
    }
}

static void eeprom_write_stage2(void)
{
    EEPROM_write_data(0x7D000, 0xFAC0, Smoke_Config_20000808);

    if ((EEPROM_Ctrl.flags1 & 0x80) != 0)
    {
        EEPROM_Ctrl.write_step += 1;
    }
    else
    {
        EEPROM_Ctrl.write_step += 2;
    }
}

static void eeprom_write_stage3(void)
{
    EEPROM_write_data(0x3F000, 0xFCC0, Smoke_Config_20000808);

    EEPROM_Ctrl.write_step += 1;
}

static void eeprom_write_done(void)
{
    EEPROM_Ctrl.write_step = 0;
    EEPROM_Ctrl.flags1 = 0;

    SysTickFlag &= ~0x01;
}

void fe_eeprom_process_run(void)
{
    uint32_t sys_tick;

    sys_tick = SysTickFlag;

    if (EEPROM_Ctrl.write_step >= 5)
    {
        eeprom_write_done();
        return;
    }

    switch (EEPROM_Ctrl.write_step)
    {
    case 0:
        if ((sys_tick & 0x03) == 0)
        {
            SysTickFlag |= 0x01;
            EEPROM_Ctrl.write_step = 1;
        }
        break;

    case 1:
        eeprom_write_stage1();
        break;

    case 2:
        eeprom_write_stage2();
        break;

    case 3:
        eeprom_write_stage3();
        break;

    default:
        EEPROM_Ctrl.write_step = 0;
        break;
    }
}

uint32_t fe_get_eeprom_state(void)
{
    return (EEPROM_Ctrl.state & 0x01) ? 0 : 1;
}