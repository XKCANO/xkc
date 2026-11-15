#include "stdint.h"

#define UART_BASE  0x40013800
#define GPIO_C     0x48002000

typedef struct {
    uint8_t mode;
    uint8_t state;
    uint16_t tx_len;
    uint16_t rx_len;
    uint8_t tx_buf[60];
    uint8_t rx_buf[60];
    uint32_t callback;
} FE_UART_TypeDef;

typedef struct {
    uint8_t rx_state;
    uint8_t tx_state;
    uint16_t rx_idx;
    uint16_t tx_idx;
    uint8_t frame_type;
    uint8_t frame_len;
    uint8_t rx_ctrl;
    uint8_t reserved;
} FE_SCI_TypeDef;

extern FE_UART_TypeDef uart;
extern FE_SCI_TypeDef Sci;

void OpenUART(void);
void CloseUART(void);
void RunSciReceivingProc(void);
void RunSciTransmittingProc(void);

void OpenUART(void)
{
    uint32_t gpio_val;
    uint32_t uart_val;

    gpio_val = *(volatile uint32_t *)(GPIO_C + 0x14);
    gpio_val |= 0x44000000;
    *(volatile uint32_t *)(GPIO_C + 0x14) = gpio_val;

    *(volatile uint32_t *)(UART_BASE + 0x08) = 0x000100D0;

    *(volatile uint32_t *)(UART_BASE + 0x04) = 9;

    uart_val = *(volatile uint32_t *)(UART_BASE + 0x10);
    uart_val |= 0x20E0;
    *(volatile uint32_t *)(UART_BASE + 0x10) = uart_val;

    uart_val = *(volatile uint32_t *)(UART_BASE + 0x04);
    uart_val |= 0xFFFF8081;
    *(volatile uint32_t *)(UART_BASE + 0x04) = uart_val;
}

void CloseUART(void)
{
    uint32_t uart_val;
    uint32_t gpio_val;

    uart_val = *(volatile uint32_t *)(UART_BASE + 0x10);
    uart_val |= 0x20E0;
    *(volatile uint32_t *)(UART_BASE + 0x10) = uart_val;

    *(volatile uint32_t *)(UART_BASE + 0x04) = 0;
    *(volatile uint32_t *)(UART_BASE + 0x1C) = 0;
    *(volatile uint32_t *)(UART_BASE + 0x20) = 0;

    gpio_val = *(volatile uint32_t *)(GPIO_C + 0x18);
    gpio_val |= 0xC000;
    *(volatile uint32_t *)(GPIO_C + 0x18) = gpio_val;
}

uint32_t fe_uart_open(uint32_t mode)
{
    OpenUART();
    uart.mode = mode;
    uart.state = 1;
    return 0;
}

uint32_t fe_get_uart_state(void)
{
    return uart.state;
}

uint32_t fe_set_uart_callback(uint32_t cb)
{
    uart.callback = cb;
    return 0;
}

void fe_uart_process_run(void)
{
    RunSciReceivingProc();
    RunSciTransmittingProc();
}