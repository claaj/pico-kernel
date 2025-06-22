#ifndef HAL_XOSC_H
#define HAL_XOSC_H

#include <stdbool.h>
#include <stdint.h>

typedef struct {
  volatile uint32_t ctrl;
  volatile uint32_t status;
  volatile uint32_t dormant;
  volatile uint32_t startup;
} xosc_hw_t;

extern xosc_hw_t *const xosc_hw;

// CTRL register
#define XOSC_CTRL_ENABLE_SHIFT 12
#define XOSC_CTRL_ENABLE_MASK (0xFFFu << 12)
#define XOSC_CTRL_ENABLE_ENABLE (0xFABu << XOSC_CTRL_ENABLE_SHIFT)
#define XOSC_CTRL_FREQ_RANGE_MASK (0xFFFu << 0)
#define XOSC_CTRL_FREQ_RANGE_1_15MHZ 0xAA0u

// STATUS register
#define XOSC_STATUS_STABLE_BITS (1u << 31)

typedef enum {
  XOSC_FREQ_1_15MHZ = XOSC_CTRL_FREQ_RANGE_1_15MHZ
} xosc_freq_range_t;

void xosc_init(xosc_freq_range_t freq_range, uint32_t startup_delay);

bool xosc_is_stable(void);

void xosc_disable(void);

#endif /* HAL_XOSC_H */
