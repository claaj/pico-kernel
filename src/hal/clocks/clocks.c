#include "clocks.h"

#include "hal/common/common.h"
#include "hal/pll/pll.h"
#include "hal/xosc/xosc.h"
#include "rp2040.h"

clocks_hw_t *const clocks_hw = (clocks_hw_t *)CLOCKS_BASE_ADDR;

void clocks_init_default(void) {
  clocks_hw->clk_sys_resus_ctrl = 0;

  xosc_init(XOSC_FREQ_1_15MHZ, 47);

  clk_ref_set_source(CLK_REF_SRC_XOSC);

  clk_sys_set_source(CLK_SYS_SRC_CLK_REF);

  pll_config_t pll_config = {
      .ref_div = 1, .fb_div = 125, .post_div1 = 6, .post_div2 = 2};
  pll_init(pll_sys_hw, &pll_config);

  clk_sys_set_source(CLK_SYS_SRC_AUX);
}

void clk_ref_set_source(clk_ref_src_t src) {
  field_write(&clocks_hw->clk_ref_ctrl, CLOCKS_CLK_REF_CTRL_SRC_MASK, 0, src);
}

void clk_sys_set_source(clk_sys_src_t src) {
  field_write(&clocks_hw->clk_sys_ctrl, CLOCKS_CLK_SYS_CTRL_SRC_MASK, 0, src);
}

uint32_t clk_sys_get_freq_hz(void) { return 125000000; }
