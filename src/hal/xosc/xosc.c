#include "xosc.h"

#include "hal/reset/reset.h"
#include "rp2040.h"

xosc_hw_t *const xosc_hw = (xosc_hw_t *)XOSC_BASE_ADDR;

void xosc_init(xosc_freq_range_t freq_range, uint32_t startup_delay) {
  unreset_peripheral(RESETS_RESET_XOSC_BITS);
  wait_for_reset_done(RESETS_RESET_XOSC_BITS);

  xosc_hw->ctrl = freq_range;

  xosc_hw->startup = startup_delay;

  xosc_hw->ctrl |= XOSC_CTRL_ENABLE_ENABLE;

  while (!xosc_is_stable()) {
    // Esperar
  }
}

bool xosc_is_stable(void) {
  return (xosc_hw->status & XOSC_STATUS_STABLE_BITS) != 0;
}

void xosc_disable(void) { xosc_hw->ctrl &= ~XOSC_CTRL_ENABLE_MASK; }
