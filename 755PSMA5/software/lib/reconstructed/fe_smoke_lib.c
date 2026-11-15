#include "stdint.h"
#include "math.h"

typedef struct {
    uint8_t mode;
    uint8_t ready;
    uint8_t step;
    uint8_t flags;
    uint8_t debug_ctrl;
    uint8_t adc_count;
    uint8_t curve_avg;
    uint8_t reserved1;
    uint32_t curve_data[32];
} Smoke_State_TypeDef;

typedef struct {
    uint32_t control;
    uint32_t cal_data[16];
    uint32_t reserved[16];
    uint32_t curve_base[16];
} Smoke_Param_TypeDef;

typedef struct {
    uint16_t adc_front[16];
    uint16_t adc_back[16];
    uint16_t density_cur;
    uint16_t density_avg;
    uint16_t density_max;
    uint16_t density_min;
    uint16_t density_u;
    uint16_t t_max;
    uint16_t t_min;
    uint16_t y_max;
    uint16_t y_min;
    uint16_t fire_thr;
    uint16_t dust_thr;
    uint16_t fault_thr;
    uint16_t linear_check;
    uint16_t fire_type;
    uint32_t curve_flags;
    uint16_t temp_rise_cnt;
    uint16_t temp_drop_cnt;
    uint16_t chamber_dust_cnt;
    uint16_t chamber_fault_cnt;
    uint16_t liquid_fire_cnt;
    uint16_t wood_fire_cnt;
    uint8_t front_dark_cnt;
    uint8_t front_bright_cnt;
    uint8_t back_dark_cnt;
    uint8_t back_bright_cnt;
    uint8_t rise_flag;
    uint8_t drop_flag;
    uint8_t dust_flag;
    uint8_t fault_flag;
    uint8_t curve_corr_cnt;
    uint8_t curve_sample_idx;
    uint8_t curve_sample[32];
} Smoke_Curve_TypeDef;

extern Smoke_State_TypeDef Smoke_State;
extern Smoke_Param_TypeDef Smoke_Param;
extern Smoke_Curve_TypeDef Smoke_Curve;
extern uint32_t SysTickFlag;
extern uint32_t Timer2Period;

extern uint32_t CalculateTargetDensity(uint32_t idx);
extern void GetCurveParameter(void *out, uint16_t *data, uint32_t len);
extern uint32_t fe_calculate_external_8b_temperature(uint32_t data);
extern uint32_t fe_calculate_crc(unsigned char *p, unsigned char l);

void OpenADC(void);
void OpenDMA(void);
void KillTimer2_ET(void);
void SetTimer2_ET(uint32_t val);
void SetADC_IN4_SCM_ET(uint32_t buf_addr);
void feed_iwdg(void);

uint32_t CalculateTargetDensity(uint32_t idx)
{
    uint32_t base;
    uint32_t offset;
    uint32_t result;

    base = (uint32_t)Smoke_Param.curve_base[4];
    offset = (base * idx) >> 7;
    result = (base + offset);

    if (base >= 0x8000)
    {
        result -= 0x10000;
    }

    return result;
}

uint32_t check_is_linear_curve(void)
{
    if (Smoke_Curve.linear_check == 0)
    {
        return 0;
    }
    return 1;
}

static void smoke_adc_init(void)
{
    uint32_t sys_ctrl;
    uint32_t gpio_cfg;

    OpenADC();
    OpenDMA();

    sys_ctrl = *(volatile uint32_t *)0x4800100C;
    sys_ctrl |= 0x10;
    *(volatile uint32_t *)0x4800100C = sys_ctrl;

    gpio_cfg = *(volatile uint32_t *)0x48000040;
    gpio_cfg |= 0x10;
    *(volatile uint32_t *)0x48000040 = gpio_cfg;

    sys_ctrl = *(volatile uint32_t *)0x4800100C;
    sys_ctrl |= 0x04;
    *(volatile uint32_t *)0x4800100C = sys_ctrl;

    gpio_cfg = *(volatile uint32_t *)0x48000040;
    gpio_cfg |= 0x04;
    *(volatile uint32_t *)0x48000040 = gpio_cfg;

    gpio_cfg = *(volatile uint32_t *)0x48000040;
    gpio_cfg |= 0x08;
    *(volatile uint32_t *)0x48000040 = gpio_cfg;
}

static void smoke_state_0(void)
{
    uint32_t control = Smoke_State.control;

    if ((control & 0x08000005) != 0)
    {
        if (Timer2Period >= 0x2000)
        {
            Timer2Period = 0;
            Smoke_State.adc_count = 1;
        }
    }

    if ((Smoke_State.adc_count & 0x80) == 0)
    {
        return;
    }

    Smoke_State.adc_count++;

    if (Smoke_State.adc_count >= 0x1F)
    {
        Smoke_State.adc_count = 0x1F;
    }
}

static void smoke_state_1(void)
{
    smoke_adc_init();
    Smoke_State.step = 2;
}

static void smoke_state_2(void)
{
    uint32_t control;

    control = Smoke_State.control;

    if ((control & 0x20000000) != 0)
    {
        Smoke_State.adc_count++;
        return;
    }

    if ((control & 0x10000000) != 0)
    {
        if ((control & 0x08000000) != 0)
        {
            *(volatile uint32_t *)0x48002040 |= 0x8000;
        }
        else
        {
            *(volatile uint32_t *)0x48001040 |= 0x200;
        }
    }
    else
    {
        if ((control & 0x08000000) != 0)
        {
            *(volatile uint32_t *)0x48002040 |= 0x2000;
        }
    }

    Smoke_State.control &= ~0x10000000;
    Smoke_State.step = 3;
}

static void smoke_state_3(void)
{
    KillTimer2_ET();

    if ((Smoke_Curve.curve_flags & 0x80000) != 0)
    {
        Smoke_Curve.density_cur = 0;
    }

    if ((Smoke_State.curve_avg & 0x80) != 0)
    {
        *(volatile uint32_t *)0x48002040 |= 0x8000;
    }
    else
    {
        if ((Smoke_State.curve_avg & 0x40) != 0)
        {
            *(volatile uint32_t *)0x48001040 |= 0x200;
        }
        if ((Smoke_State.curve_avg & 0x20) != 0)
        {
            *(volatile uint32_t *)0x48002040 |= 0x2000;
        }
        if ((Smoke_State.curve_avg & 0x10) != 0)
        {
            *(volatile uint32_t *)0x48001040 |= 0x4000;
        }
    }

    Smoke_State.step = 4;
}

static void smoke_state_4(void)
{
    SetTimer2_ET(0x1194);
    SysTickFlag = 0x200002F8;
    SetADC_IN4_SCM_ET(&Smoke_Curve);
    Smoke_State.adc_count++;
}

static void smoke_default_state(void)
{
    Smoke_State.adc_count++;
}

static void smoke_state_machine(void)
{
    uint8_t state;

    state = Smoke_State.adc_count & 0x1F;

    switch (state)
    {
    case 0x00:
    case 0x01:
    case 0x02:
    case 0x03:
    case 0x04:
    case 0x05:
    case 0x06:
    case 0x07:
    case 0x08:
    case 0x09:
    case 0x0A:
    case 0x0B:
    case 0x0C:
    case 0x0D:
    case 0x0E:
        smoke_state_0();
        break;

    case 0x0F:
        smoke_state_1();
        break;

    case 0x10:
        smoke_state_2();
        break;

    case 0x11:
        smoke_state_3();
        break;

    case 0x12:
        smoke_state_4();
        break;

    default:
        smoke_default_state();
        break;
    }
}

static uint32_t CheckIsChamberDust(void)
{
    uint32_t control = Smoke_State.control;
    uint16_t target;
    uint16_t thresh;
    int16_t idx;
    uint16_t curve_val;
    uint16_t offset;
    uint16_t dust_threshold;
    uint16_t dust_ref;

    if ((control & 0x20000000) != 0)
    {
        target = (uint16_t)(0x4000 - Smoke_Param.curve_base[3]);
        thresh = Smoke_Curve.fire_thr;

        if (thresh >= target)
        {
            Smoke_Curve.dust_flag++;
            Smoke_Curve.temp_rise_cnt = 0;
            Smoke_Curve.temp_drop_cnt = 0;
            return 1;
        }
        else
        {
            Smoke_Curve.dust_flag = 0;
            if (Smoke_Curve.dust_flag < 0xFF)
            {
                Smoke_Curve.dust_flag++;
            }
        }
    }
    else
    {
        idx = (int16_t)(Smoke_Param.reserved[0] * Smoke_Param.reserved[1]);
        curve_val = (uint16_t)(Smoke_Curve.density_avg + idx);

        offset = (uint16_t)(Smoke_Param.curve_base[4] * 13 / 128);
        offset += (uint16_t)(Smoke_Param.curve_base[4] * 3 / 128);

        if (curve_val >= Smoke_Curve.curve_flags)
        {
            Smoke_Curve.chamber_dust_cnt++;
            Smoke_Curve.fire_type = 0;
            Smoke_Curve.linear_check = 0;
            return 1;
        }
        else
        {
            Smoke_Curve.chamber_dust_cnt = 0;
            if (Smoke_Curve.chamber_dust_cnt < 0xFF)
            {
                Smoke_Curve.chamber_dust_cnt++;
            }
        }
    }

    return 0;
}

static uint32_t CheckIsChamberFault(void)
{
    uint32_t control = Smoke_State.control;

    if ((control & 0x20000000) != 0)
    {
        uint16_t ref = Smoke_Curve.density_cur;
        uint16_t fault_thr = Smoke_Curve.fault_thr;

        if (fault_thr > ref)
        {
            uint16_t diff = ref;
            uint16_t target;
            int16_t idx;

            target = (uint16_t)(0x4000 - Smoke_Param.curve_base[3]);
            idx = (int16_t)(Smoke_Param.reserved[0] * Smoke_Param.reserved[1]);
            diff = (uint16_t)(target - idx);

            if (diff < fault_thr)
            {
                Smoke_Curve.fault_flag++;
                return 1;
            }
            else
            {
                Smoke_Curve.fault_flag = 0;
            }
        }
    }
    else
    {
        if (Smoke_Curve.density_cur >= Smoke_Curve.fault_thr)
        {
            uint16_t max_ref = (uint16_t)(Smoke_Curve.t_max * Smoke_Curve.y_max >> 8);
            uint16_t min_ref = (uint16_t)(Smoke_Curve.t_min * Smoke_Curve.y_min >> 8);

            if (max_ref <= Smoke_Curve.fire_thr || min_ref >= Smoke_Curve.fire_thr)
            {
                Smoke_Curve.fault_flag++;
                return 1;
            }
        }
    }

    return 0;
}

static uint32_t CheckIsFire(void)
{
    uint32_t density;
    uint32_t target_19;
    uint32_t target_12;

    target_19 = CalculateTargetDensity(0x13);
    target_12 = CalculateTargetDensity(0x0C);

    if (Smoke_Curve.t_max < target_19) return 0;
    if (Smoke_Curve.y_max < target_19) return 0;
    if (Smoke_Curve.t_min < target_12) return 0;
    if (Smoke_Curve.y_min < target_12) return 0;

    if (Smoke_Curve.y_max <= 0) return 0;
    if (Smoke_Curve.y_min <= 0) return 0;

    if (Smoke_Curve.density_cur > Smoke_Curve.fire_thr) return 0;

    return 1;
}

static uint32_t CheckIsLiquidFire(void)
{
    uint32_t target_19 = CalculateTargetDensity(0x13);

    if (Smoke_Curve.t_max < target_19) return 0;
    if (Smoke_Curve.t_max > 0x8000) return 0;
    if (Smoke_Curve.y_max < target_19) return 0;
    if (Smoke_Curve.y_max > 0x8000) return 0;
    if (Smoke_Curve.t_min < 0x100) return 0;
    if (Smoke_Curve.y_min < 0x100) return 0;
    if (Smoke_Curve.density_cur < 0x300) return 0;

    return 1;
}

static uint32_t CheckIsWoodFire(void)
{
    uint32_t target_19 = CalculateTargetDensity(0x13);
    uint32_t target_12 = CalculateTargetDensity(0x0C);

    if (Smoke_Curve.t_max < target_19) return 0;
    if (Smoke_Curve.t_max > Smoke_Curve.density_cur) return 0;
    if (Smoke_Curve.t_min < target_12) return 0;

    if (Smoke_Param.reserved[8] <= Smoke_Curve.t_min) return 0;
    if (Smoke_Param.reserved[14] <= Smoke_Curve.y_max) return 0;

    return 1;
}

static uint32_t CheckIsTemperatureChange(uint32_t threshold)
{
    uint8_t temp_prev = (uint8_t)Smoke_Param.cal_data[0xD];
    uint8_t temp_now = (uint8_t)Smoke_Param.cal_data[1];
    int32_t cmp_val;

    cmp_val = (int32_t)(temp_prev - temp_now);

    if (cmp_val == 0)
    {
        Smoke_State.control &= ~(3u << 29);
    }
    else
    {
        if ((uint8_t)(abs(cmp_val) - 1) > 0x7F)
        {
            return 0;
        }

        Smoke_State.control |= (3u << 29);
        Smoke_Param.cal_data[1] = temp_prev;
        Smoke_Curve.linear_check = 0;
    }

    return 0;
}

static uint32_t CheckIsTemperatureRise(uint32_t threshold)
{
    uint8_t temp_prev = (uint8_t)Smoke_Param.cal_data[0xE];
    uint8_t temp_now = (uint8_t)Smoke_Param.cal_data[5];
    int32_t cmp_val;

    cmp_val = (int32_t)(temp_prev - temp_now);

    if ((Smoke_State.control & 0x20000) != 0)
    {
        if ((Smoke_State.control & 0x10000) == 0)
        {
            if (cmp_val == 1)
            {
                Smoke_State.control |= 0x1000;
                Smoke_Curve.temp_rise_cnt = 0;
            }
        }
        else
        {
            if (cmp_val != 1)
            {
                Smoke_Curve.temp_rise_cnt++;
                if (Smoke_Curve.temp_rise_cnt >= threshold)
                {
                    Smoke_State.control &= ~0x1000;
                }
            }
        }
    }
    else
    {
        if (cmp_val == 1)
        {
            Smoke_State.control |= (1u << 13);
            Smoke_State.control &= ~((3u << 22));
            Smoke_Curve.temp_rise_cnt = 0;
        }
    }

    return 0;
}

static uint32_t CheckIsTemperatureDrop(uint32_t threshold)
{
    uint8_t temp_prev = (uint8_t)Smoke_Param.cal_data[0xF];
    uint8_t temp_now = (uint8_t)Smoke_Param.cal_data[5];
    int32_t cmp_val;

    cmp_val = (int32_t)(temp_prev - temp_now);

    if ((Smoke_State.control & 0x40000) != 0)
    {
        if ((Smoke_State.control & 0x80000000) != 0)
        {
            if (cmp_val == -1)
            {
                Smoke_State.control |= 0x4000;
                Smoke_Curve.temp_drop_cnt = 0;
            }
        }
        else
        {
            if (cmp_val != -1)
            {
                Smoke_Curve.temp_drop_cnt++;
                if (Smoke_Curve.temp_drop_cnt >= threshold)
                {
                    Smoke_State.control &= ~0x4000;
                }
            }
        }
    }
    else
    {
        if (cmp_val == -1)
        {
            Smoke_State.control |= (1u << 15);
            Smoke_State.control &= ~((3u << 29));
            Smoke_Curve.temp_drop_cnt = 0;
        }
    }

    return 0;
}

static uint32_t CheckIsDangerousState(void)
{
    if ((Smoke_State.control & 0x4000) != 0 && (Smoke_State.control & 0x1000) != 0)
    {
        return 1;
    }
    if ((Smoke_State.control & 0x00040000) != 0 && (Smoke_State.control & 0x00100000) != 0)
    {
        return 1;
    }
    if ((Smoke_State.control & 0x20000000) != 0 && (Smoke_State.control & 0x10000000) != 0)
    {
        return 1;
    }
    if ((Smoke_State.control & 0x40000000) != 0 && (Smoke_State.control & 0x80000000) != 0)
    {
        return 1;
    }
    if ((Smoke_State.control & 0x2000000) != 0 && (Smoke_State.control & 0x4000000) != 0)
    {
        return 1;
    }
    return 0;
}

static uint32_t CheckIsSafeState(void)
{
    uint32_t target_19 = CalculateTargetDensity(0x13);
    uint32_t target_12 = CalculateTargetDensity(0x0C);
    uint32_t target_20 = CalculateTargetDensity(0x14);

    if (Smoke_Curve.t_max >= target_19) return 0;
    if (Smoke_Curve.t_min >= target_12) return 0;
    if (Smoke_Curve.y_max <= target_19) return 0;
    if (Smoke_Curve.y_min <= target_12) return 0;

    if (Smoke_Curve.fire_type >= target_19 &&
        Smoke_Curve.fire_type <= target_20 &&
        Smoke_Curve.linear_check != 0)
    {
        return 0;
    }

    if (Smoke_Curve.fire_type <= target_12)
    {
        return 0;
    }

    if ((Smoke_State.control & 0x40000) != 0)
    {
        if (Smoke_Curve.t_max > 0 && Smoke_Curve.t_max <= 0x2000 &&
            Smoke_Curve.t_min > 0 && Smoke_Curve.t_min <= 0x2000 &&
            Smoke_Curve.y_max > 0 && Smoke_Curve.y_max <= 0x4000 &&
            Smoke_Curve.y_min > 0 && Smoke_Curve.y_min <= 0x4000)
        {
            return 0;
        }
    }

    return 1;
}

static void smoke_detect_process(void)
{
    CheckIsTemperatureChange(0x01);
    CheckIsTemperatureRise(0x01);
    CheckIsTemperatureDrop(0x01);

    if (CheckIsChamberFault())
    {
        return;
    }

    if (CheckIsChamberDust())
    {
        return;
    }

    if (CheckIsLiquidFire())
    {
        Smoke_Curve.fire_type = 1;
        return;
    }

    if (CheckIsWoodFire())
    {
        Smoke_Curve.fire_type = 2;
        return;
    }

    if (CheckIsFire())
    {
        Smoke_Curve.fire_type = 3;
        return;
    }
}

void fe_smoke_process_run(void)
{
    smoke_state_machine();
    smoke_detect_process();
    feed_iwdg();
}

uint32_t fe_start_up_smoke_process(uint32_t mode)
{
    if (Smoke_State.curve_avg != 0)
    {
        if ((Smoke_State.control & 0x10000000) != 0)
        {
            return 1;
        }
    }

    if (mode == 0)
    {
        Smoke_State.control ^= (1u << 26);
        Smoke_State.curve_avg |= 0x80;
        return 0;
    }
    else if (mode == 1)
    {
        Smoke_State.debug_ctrl = 7;
        Smoke_State.flags = 0xAA;
        Smoke_State.curve_avg = 0;
        Smoke_State.control = 0;
        Smoke_State.adc_count = 0;
        Smoke_State.step = 0;
        Smoke_State.ready = 1;
        return 0;
    }
    else if (mode == 2)
    {
        Smoke_State.curve_avg = 0;
        Smoke_State.debug_ctrl = 7;
        return 0;
    }

    return 1;
}

uint32_t fe_set_main_power_source(void)
{
    *(volatile uint32_t *)0x48001040 |= 0x00000200;
    return 0;
}

uint32_t fe_set_backup_power_source(void)
{
    *(volatile uint32_t *)0x48002040 |= 0x00008000;
    return 0;
}

uint32_t fe_start_up_smoke_sampling(void)
{
    Smoke_State.control |= 0x10000000;
    return 0;
}

uint32_t fe_stop_smoke_sampling(void)
{
    Smoke_State.control &= ~0x10000000;
    return 0;
}

uint32_t fe_get_smoke_state(void)
{
    if ((Smoke_State.control & 0x4000) != 0 || (Smoke_State.control & 0x1000) != 0)
    {
        return 1;
    }
    return 0;
}