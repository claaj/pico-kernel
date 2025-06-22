#ifndef HAL_PLL_H
#define HAL_PLL_H

#include <stdbool.h>
#include <stdint.h>

typedef struct {
  volatile uint32_t cs;
  volatile uint32_t pwr;
  volatile uint32_t fbdiv_int;
  volatile uint32_t prim;
} pll_hw_t;

extern pll_hw_t *const pll_sys_hw;
extern pll_hw_t *const pll_usb_hw;

// CS register
#define PLL_CS_LOCK_BITS (1u << 31)
#define PLL_CS_REFDIV_SHIFT 0
#define PLL_CS_REFDIV_MASK (0x3Fu << 0)

// PWR register
#define PLL_PWR_PD_BITS (1u << 0)
#define PLL_PWR_POSTDIVPD_BITS (1u << 3)
#define PLL_PWR_VCOPD_BITS (1u << 5)

// PRIM register
#define PLL_PRIM_POSTDIV2_SHIFT 12
#define PLL_PRIM_POSTDIV2_MASK (0x7u << 12)
#define PLL_PRIM_POSTDIV1_SHIFT 16
#define PLL_PRIM_POSTDIV1_MASK (0x7u << 16)

typedef struct {
  uint32_t ref_div;
  uint32_t fb_div;
  uint32_t post_div1;
  uint32_t post_div2;
} pll_config_t;

void pll_init(pll_hw_t *pll, const pll_config_t *config);

bool pll_is_locked(pll_hw_t *pll);

void pll_deinit(pll_hw_t *pll);

uint32_t pll_get_freq_hz(pll_hw_t *pll, uint32_t ref_freq_hz);

#endif /* HAL_PLL_H */
