#include "reset.h"

#include "rp2040.h"

resets_hw_t *const resets_hw = (resets_hw_t *)RESETS_BASE_ADDR;

void reset_peripheral(uint32_t reset_bits) { resets_hw->reset |= reset_bits; }

void unreset_peripheral(uint32_t reset_bits) {
  resets_hw->reset &= ~reset_bits;
}

bool is_peripheral_reset_done(uint32_t reset_bits) {
  return (resets_hw->reset_done & reset_bits) == reset_bits;
}

void wait_for_reset_done(uint32_t reset_bits) {
  while (!is_peripheral_reset_done(reset_bits)) {
    // Esperar
  }
}
