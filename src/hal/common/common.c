#include "common.h"

void delay_cycles(uint32_t cycles) {
  for (volatile uint32_t i = 0; i < cycles; ++i) {
    __asm volatile("nop");
  }
}
