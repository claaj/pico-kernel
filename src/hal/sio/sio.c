#include "sio.h"

#include "hal/common/common.h"
#include "rp2040.h"

sio_hw_t *const sio_hw = (sio_hw_t *)SIO_BASE_ADDR;

void gpio_set_output_enabled(uint32_t pin, bool enabled) {
  if (pin >= 30)
    return;

  if (enabled) {
    bit_set(&sio_hw->gpio_oe_set, pin);
  } else {
    bit_set(&sio_hw->gpio_oe_clr, pin);
  }
}

void gpio_set_output_level(uint32_t pin, bool level) {
  if (pin >= 30)
    return;

  if (level) {
    bit_set(&sio_hw->gpio_out_set, pin);
  } else {
    bit_set(&sio_hw->gpio_out_clr, pin);
  }
}

void gpio_toggle_output_level(uint32_t pin) {
  if (pin >= 30)
    return;

  bit_set(&sio_hw->gpio_out_xor, pin);
}

bool gpio_get_input_level(uint32_t pin) {
  if (pin >= 30)
    return false;

  return bit_is_set(sio_hw->gpio_in, pin);
}

uint32_t gpio_get_all_inputs(void) { return sio_hw->gpio_in; }
