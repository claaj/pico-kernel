#ifndef HAL_CLOCKS_H
#define HAL_CLOCKS_H

#include <stdint.h>

typedef struct {
  uint32_t _unused0[0x30 / 4];
  volatile uint32_t clk_ref_ctrl;     // 0x30
  volatile uint32_t clk_ref_div;      // 0x34
  volatile uint32_t clk_ref_selected; // 0x38
  volatile uint32_t clk_sys_ctrl;     // 0x3c
  volatile uint32_t clk_sys_div;      // 0x40
  volatile uint32_t clk_sys_selected; // 0x44
  uint32_t _unused1[(0x78 - 0x44 - 4) / 4];
  volatile uint32_t clk_sys_resus_ctrl; // 0x78
} clocks_hw_t;

extern clocks_hw_t *const clocks_hw;

typedef enum {
  CLK_REF_SRC_ROSC = 0,
  CLK_REF_SRC_AUX = 1,
  CLK_REF_SRC_XOSC = 2
} clk_ref_src_t;

typedef enum {
  CLK_SYS_SRC_CLK_REF = 0,
  CLK_SYS_SRC_AUX = 1 // AUX = PLL_SYS por defecto
} clk_sys_src_t;

#define CLOCKS_CLK_REF_CTRL_SRC_MASK (0x3u << 0)
#define CLOCKS_CLK_SYS_CTRL_SRC_MASK (0x1u << 0)

void clocks_init_default(void);

void clk_ref_set_source(clk_ref_src_t src);

void clk_sys_set_source(clk_sys_src_t src);

uint32_t clk_sys_get_freq_hz(void);

#endif /* HAL_CLOCKS_H */
