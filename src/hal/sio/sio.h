#ifndef HAL_SIO_H
#define HAL_SIO_H

#include <stdbool.h>
#include <stdint.h>

typedef struct {
  volatile uint32_t cpuid;
  volatile uint32_t gpio_in;
  volatile uint32_t gpio_hi_in;
  uint32_t _reserved0;
  volatile uint32_t gpio_out;
  volatile uint32_t gpio_out_set;
  volatile uint32_t gpio_out_clr;
  volatile uint32_t gpio_out_xor;
  volatile uint32_t gpio_oe;
  volatile uint32_t gpio_oe_set;
  volatile uint32_t gpio_oe_clr;
  volatile uint32_t gpio_oe_xor;
} sio_hw_t;

extern sio_hw_t *const sio_hw;

void gpio_set_output_enabled(uint32_t pin, bool enabled);

void gpio_set_output_level(uint32_t pin, bool level);

void gpio_toggle_output_level(uint32_t pin);

bool gpio_get_input_level(uint32_t pin);

uint32_t gpio_get_all_inputs(void);

#endif /* HAL_SIO_H */
