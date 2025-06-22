#ifndef HAL_UART_H
#define HAL_UART_H

#include <stdint.h>

typedef struct {
  volatile uint32_t dr;
  uint32_t _pad[17];
} uart_hw_t;

extern uart_hw_t *const uart0_hw;

void uart_init(void);

void uart_putc(char c);

#endif /* HAL_UART_H */
