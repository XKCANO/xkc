#include "stdint.h"

typedef struct {
    uint8_t mode;
    uint8_t ready;
    uint8_t step;
    uint8_t adc_count;
    uint8_t flags;
    uint16_t voltage;
    uint16_t low_thr;
    uint8_t adc_buffer[8];
    uint32_t callback;
} FE_BATTERY_TypeDef;

extern FE_BATTERY_TypeDef Battery;
extern volatile uint32_t SysTickFlag;
extern uint32_t Timer3Period;

void OpenADC(void);
void SetADC_IN8_SCM(void);
void SetTimer3(uint32_t val);
void KillTimer3(void);

uint32_t fe_start_up_battery_process(uint32_t mode)
{
    if (mode != 0)
    {
        Battery.mode |= 0x02;
        return 0;
    }

    if (Battery.ready != 0)
    {
        return 1;
    }

    Battery.ready = 1;
    return 0;
}

static void battery_state_machine(void)
{
    if ((Battery.flags & 0x20) == 0)
    {
        if (SysTickFlag >= 0x3e8)
        {
            SysTickFlag = 0;
            Battery.adc_buffer[7] = 1;
        }
        return;
    }

    switch (Battery.step)
    {
    case 0:
        if ((Battery.mode & 0x03) != 0)
        {
            Battery.step = 1;
            OpenADC();
            SetADC_IN8_SCM();
        }
        break;

    case 1:
        {
            uint32_t reg_val;
            reg_val = *(volatile uint32_t *)0x48001040;
            reg_val |= 0x01;
            *(volatile uint32_t *)0x48001040 = reg_val;

            reg_val = *(volatile uint32_t *)0x48001040;
            reg_val |= 0x02;
            *(volatile uint32_t *)0x48001040 = reg_val;

            reg_val = *(volatile uint32_t *)0x48001000;
            reg_val |= 0x02;
            *(volatile uint32_t *)0x48001000 = reg_val;

            reg_val = *(volatile uint32_t *)0x48001040;
            reg_val |= 0x02;
            *(volatile uint32_t *)0x48001040 = reg_val;

            SysTickFlag &= ~0x02;

            if ((Battery.flags & 0x80) != 0)
            {
                Battery.adc_count++;
                if (Battery.adc_count >= 3)
                {
                    Battery.flags |= 0x01;
                }
            }
            else
            {
                Battery.adc_count = 0;
            }
            Battery.step = 2;
        }
        break;

    case 2:
        SetTimer3(0xFFF5);
        Battery.step = 0;
        break;

    default:
        Battery.step = 0;
        break;
    }
}

static void battery_adc_process(void)
{
    uint32_t adc_val;
    uint32_t threshold = 0x2ee0;

    if ((Battery.flags & 0x20) != 0)
    {
        if ((Battery.flags & 0x80) == 0)
        {
            Battery.flags |= 0x80;
        }

        if (Battery.voltage > threshold)
        {
            Battery.flags &= ~0x40;
        }
        else
        {
            Battery.flags |= 0x40;
        }
    }
}

static void battery_check_voltage(void)
{
    if ((Battery.flags & 0x01) != 0)
    {
        Battery.flags |= 0x10;
    }
    else
    {
        Battery.flags &= ~0x10;
    }
}

void fe_battery_process_run(void)
{
    battery_state_machine();

    if ((Battery.adc_buffer[7] & 0x80) != 0)
    {
        if ((Battery.flags & 0x20) == 0)
        {
            if (SysTickFlag >= 0x3e8)
            {
                SysTickFlag = 0;
                Battery.adc_buffer[7] = 1;
            }
            return;
        }

        KillTimer3();
        battery_adc_process();
        battery_check_voltage();

        Battery.adc_buffer[7] = 0;
    }
}

uint32_t fe_set_battery_callback(uint32_t cb)
{
    Battery.callback = cb;
    return 0;
}

uint32_t fe_get_battery_state(void)
{
    return (Battery.flags & 0x10) ? 1 : 0;
}