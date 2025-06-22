#ifndef HAL_PAD_BANK_H
#define HAL_PAD_BANK_H

#include <stdbool.h>
#include <stdint.h>

typedef struct {
  volatile uint32_t voltage_select;
  volatile uint32_t gpio[30]; // GPIO0-GPIO29
  volatile uint32_t swclk;
  volatile uint32_t swd;
} pad_bank_hw_t;

extern pad_bank_hw_t *const pad_bank_hw;

#define PAD_OD_SHIFT 7
#define PAD_IE_SHIFT 6
#define PAD_DRIVE_SHIFT 4
#define PAD_PUE_SHIFT 3
#define PAD_PDE_SHIFT 2
#define PAD_SCHMITT_SHIFT 1
#define PAD_SLEWFAST_SHIFT 0

#define PAD_DRIVE_2MA 0
#define PAD_DRIVE_4MA 1
#define PAD_DRIVE_8MA 2
#define PAD_DRIVE_12MA 3

typedef struct {
  bool output_disable;
  bool input_enable;
  uint32_t drive_strength; // PAD_DRIVE_*
  bool pull_up_enable;
  bool pull_down_enable;
  bool schmitt_enable;
  bool slew_fast;
} pad_config_t;

void gpio_set_pad_config(uint32_t pin, const pad_config_t *config);

void gpio_init_pin(uint32_t pin, uint32_t function,
                   const pad_config_t *pad_config);

#endif /* HAL_PAD_BANK_H */
