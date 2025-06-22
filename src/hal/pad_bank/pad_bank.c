#include "pad_bank.h"

#include "hal/io_bank/io_bank.h"
#include "hal/reset/reset.h"
#include "rp2040.h"

pad_bank_hw_t *const pad_bank_hw = (pad_bank_hw_t *)PADS_BANK0_BASE_ADDR;

void gpio_set_pad_config(uint32_t pin, const pad_config_t *config) {
  if (pin >= 30)
    return;

  uint32_t pad_val = (config->output_disable << PAD_OD_SHIFT) |
                     (config->input_enable << PAD_IE_SHIFT) |
                     (config->drive_strength << PAD_DRIVE_SHIFT) |
                     (config->pull_up_enable << PAD_PUE_SHIFT) |
                     (config->pull_down_enable << PAD_PDE_SHIFT) |
                     (config->schmitt_enable << PAD_SCHMITT_SHIFT) |
                     (config->slew_fast << PAD_SLEWFAST_SHIFT);

  pad_bank_hw->gpio[pin] = pad_val;
}

void gpio_init_pin(uint32_t pin, uint32_t function,
                   const pad_config_t *pad_config) {
  if (pin >= 30)
    return;

  // IO_BANK0 y PADS_BANK0 fuera de reset
  static bool peripherals_initialized = false;
  if (!peripherals_initialized) {
    unreset_peripheral(RESETS_RESET_IO_BANK0_BITS |
                       RESETS_RESET_PADS_BANK0_BITS);
    wait_for_reset_done(RESETS_RESET_IO_BANK0_BITS |
                        RESETS_RESET_PADS_BANK0_BITS);
    peripherals_initialized = true;
  }

  gpio_set_pad_config(pin, pad_config);

  gpio_set_function(pin, function);
}
