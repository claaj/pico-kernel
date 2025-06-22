#include "uart.h"

#include "hal/io_bank/io_bank.h"
#include "hal/reset/reset.h"

uart_hw_t *const uart0_hw = (uart_hw_t *)0x40034000;
uart_hw_t *const uart1_hw = (uart_hw_t *)0x40038000;

void uart_init(void) {
  unreset_peripheral(1u << 22);

  gpio_set_function(0, 2); // TX
  gpio_set_function(1, 2); // RX

  uart0_hw->dr = 67;                          // IBRD
  *(volatile uint32_t *)(0x40034028) = 52;    // FBRD
  *(volatile uint32_t *)(0x4003402C) = 0x60;  // LCR_H (8 bits)
  *(volatile uint32_t *)(0x40034030) = 0x301; // CR (enable all)
}

void uart_putc(char c) { uart0_hw->dr = c; }
