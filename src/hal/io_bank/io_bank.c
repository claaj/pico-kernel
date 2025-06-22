#include "io_bank.h"

#include "rp2040.h"

io_bank_hw_t *const io_bank_hw = (io_bank_hw_t *)IO_BANK0_BASE_ADDR;

void gpio_set_function(uint32_t pin, uint32_t function) {
  if (pin >= 30)
    return;

  io_bank_hw->gpio[pin].ctrl = function;
}

uint32_t gpio_get_function(uint32_t pin) {
  if (pin >= 30)
    return GPIO_FUNC_NULL;

  return io_bank_hw->gpio[pin].ctrl & 0x1f;
}
