#ifndef HAL_RESET_H
#define HAL_RESET_H

#include <stdbool.h>
#include <stdint.h>

typedef struct {
  volatile uint32_t reset;
  volatile uint32_t wdsel;
  volatile uint32_t reset_done;
} resets_hw_t;

extern resets_hw_t *const resets_hw;

#define RESETS_RESET_IO_BANK0_BITS (1u << 5)
#define RESETS_RESET_PADS_BANK0_BITS (1u << 8)
#define RESETS_RESET_PLL_SYS_BITS (1u << 12)
#define RESETS_RESET_XOSC_BITS (1u << 13)

void reset_peripheral(uint32_t reset_bits);

void unreset_peripheral(uint32_t reset_bits);

bool is_peripheral_reset_done(uint32_t reset_bits);

void wait_for_reset_done(uint32_t reset_bits);

#endif /* HAL_RESET_H */
