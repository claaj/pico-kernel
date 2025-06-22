#include "pll.h"

#include "hal/common/common.h"
#include "hal/reset/reset.h"
#include "rp2040.h"

pll_hw_t *const pll_sys_hw = (pll_hw_t *)PLL_SYS_BASE_ADDR;
pll_hw_t *const pll_usb_hw = (pll_hw_t *)PLL_USB_BASE_ADDR;

void pll_init(pll_hw_t *pll, const pll_config_t *config) {
  uint32_t reset_bit = (pll == pll_sys_hw) ? RESETS_RESET_PLL_SYS_BITS : 0;

  if (reset_bit) {
    unreset_peripheral(reset_bit);
    wait_for_reset_done(reset_bit);
  }

  field_write(&pll->cs, PLL_CS_REFDIV_MASK, PLL_CS_REFDIV_SHIFT,
              config->ref_div);

  pll->fbdiv_int = config->fb_div;

  pll->pwr = PLL_PWR_PD_BITS | PLL_PWR_VCOPD_BITS;

  pll->pwr &= ~PLL_PWR_POSTDIVPD_BITS;

  pll->prim = (config->post_div1 << PLL_PRIM_POSTDIV1_SHIFT) |
              (config->post_div2 << PLL_PRIM_POSTDIV2_SHIFT);

  pll->pwr &= ~(PLL_PWR_PD_BITS | PLL_PWR_VCOPD_BITS);

  // Esperar lock
  while (!pll_is_locked(pll)) {
  }
}

bool pll_is_locked(pll_hw_t *pll) { return (pll->cs & PLL_CS_LOCK_BITS) != 0; }

void pll_deinit(pll_hw_t *pll) {
  pll->pwr = PLL_PWR_PD_BITS | PLL_PWR_VCOPD_BITS | PLL_PWR_POSTDIVPD_BITS;
}

uint32_t pll_get_freq_hz(pll_hw_t *pll, uint32_t ref_freq_hz) {
  uint32_t ref_div =
      field_get(pll->cs, PLL_CS_REFDIV_MASK, PLL_CS_REFDIV_SHIFT);
  uint32_t fb_div = pll->fbdiv_int;
  uint32_t post_div1 =
      field_get(pll->prim, PLL_PRIM_POSTDIV1_MASK, PLL_PRIM_POSTDIV1_SHIFT);
  uint32_t post_div2 =
      field_get(pll->prim, PLL_PRIM_POSTDIV2_MASK, PLL_PRIM_POSTDIV2_SHIFT);

  return (ref_freq_hz / ref_div) * fb_div / (post_div1 * post_div2);
}
