#ifndef HAL_IO_BANK_H
#define HAL_IO_BANK_H

#include <stdbool.h>
#include <stdint.h>

typedef struct {
  volatile uint32_t status;
  volatile uint32_t ctrl;
} io_bank_gpio_t;

typedef struct {
  io_bank_gpio_t gpio[30]; // GPIO0-GPIO29
  volatile uint32_t intr[4];
  volatile uint32_t inte[4];
  volatile uint32_t intf[4];
  volatile uint32_t ints[4];
} io_bank_hw_t;

extern io_bank_hw_t *const io_bank_hw;

// GPIO Functions
#define GPIO_FUNC_SPI 1
#define GPIO_FUNC_UART 2
#define GPIO_FUNC_I2C 3
#define GPIO_FUNC_PWM 4
#define GPIO_FUNC_SIO 5
#define GPIO_FUNC_PIO0 6
#define GPIO_FUNC_PIO1 7
#define GPIO_FUNC_CLOCK 8
#define GPIO_FUNC_USB 9
#define GPIO_FUNC_NULL 31

void gpio_set_function(uint32_t pin, uint32_t function);
uint32_t gpio_get_function(uint32_t pin);

#endif /* HAL_IO_BANK_H */
