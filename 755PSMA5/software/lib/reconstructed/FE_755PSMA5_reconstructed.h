#ifndef __FE_755PSMA5_RECONSTRUCTED_H
#define __FE_755PSMA5_RECONSTRUCTED_H

#include "stdint.h"

#ifdef __cplusplus
extern "C" {
#endif

#define FE_OK       0
#define FE_ERROR    1
#define FE_SUCCESS  0

typedef void (*FE_SMOKE_CALLBACK)(uint32_t param);
typedef void (*FE_BATTERY_CALLBACK)(uint32_t param);
typedef void (*FE_UART_CALLBACK)(uint32_t p, uint32_t l);

typedef struct {
    uint32_t average;
    uint32_t max;
    uint32_t min;
    uint32_t u;
} FE_CURVE_AVERAGE_TypeDef;

typedef struct {
    uint16_t t_max;
    uint16_t y_max;
    uint16_t t_min;
    uint16_t y_min;
    uint16_t y_u;
} FE_CURVE_AMPLITUDE_TypeDef;

void fe_smoke_process_run(void);
uint32_t fe_set_smoke_callback(FE_SMOKE_CALLBACK cb);
uint32_t fe_start_up_smoke_process(uint32_t mode);
uint32_t fe_start_up_smoke_sampling(void);
uint32_t fe_stop_smoke_sampling(void);
uint32_t fe_set_main_power_source(void);
uint32_t fe_set_backup_power_source(void);
uint32_t fe_get_smoke_state(void);

void fe_battery_process_run(void);
uint32_t fe_set_battery_callback(FE_BATTERY_CALLBACK cb);
uint32_t fe_start_up_battery_process(uint32_t mode);
uint32_t fe_get_battery_state(void);

void fe_eeprom_process_run(void);
uint32_t fe_get_eeprom_state(void);
void fe_smoke_read_eeprom_data(void);

void fe_uart_process_run(void);
uint32_t fe_uart_open(uint32_t mode);
uint32_t fe_get_uart_state(void);
uint32_t fe_set_uart_callback(FE_UART_CALLBACK cb);

uint32_t fe_calculate_crc(unsigned char *p, unsigned char l);
uint32_t fe_calculate_crc16(unsigned char *p, unsigned char l);
uint32_t fe_correcting_ad_data(uint32_t data, uint32_t vref);
float fe_get_filter(float f, uint32_t data);
float fe_get_filter2(float f, uint32_t data);
uint32_t fe_get_average(uint16_t *p, uint32_t l);
uint32_t fe_get_maximum(uint16_t *p, uint32_t l);
uint32_t fe_get_minimum(uint16_t *p, uint32_t l);
uint32_t fe_get_increment(uint16_t *p, uint32_t l);
void fe_float_data_move_to_left(float *p, uint32_t l);
void fe_float_data_move_to_right(float *p, uint32_t l);
void fe_data_move_to_left(uint16_t *p, uint32_t l);
void fe_data_move_to_right(uint16_t *p, uint32_t l);
void fe_byte_data_move_to_left(unsigned char *p, uint32_t l);
uint32_t fe_comparision(uint32_t t1, uint32_t t2);
uint32_t fe_char_real_comparision(unsigned char t1, unsigned char t2);
uint32_t fe_subtractive(uint32_t t1, uint32_t t2);
uint32_t fe_char_real_subtractive(unsigned char t1, unsigned char t2);
void fe_get_curve_average(FE_CURVE_AVERAGE_TypeDef *p, uint16_t *pd, uint32_t l);
void fe_get_curve_amplitude(FE_CURVE_AMPLITUDE_TypeDef *p, uint16_t *pd, uint32_t l);
uint32_t fe_calculate_external_temperature(uint32_t data);
uint32_t fe_calculate_external_8b_temperature(uint32_t data);

#ifdef __cplusplus
}
#endif

#endif