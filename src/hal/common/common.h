#ifndef COMMON_H
#define COMMON_H

#include <stdbool.h>
#include <stdint.h>

static inline uint32_t bit(uint32_t n) { return 1u << n; }

static inline uint32_t mask_create(uint32_t width, uint32_t shift) {
  return ((1u << width) - 1) << shift;
}

static inline uint32_t field_get(uint32_t reg, uint32_t mask, uint32_t shift) {
  return (reg & mask) >> shift;
}

static inline uint32_t field_set(uint32_t reg, uint32_t mask, uint32_t shift,
                                 uint32_t value) {
  return (reg & ~mask) | ((value << shift) & mask);
}

static inline void field_write(volatile uint32_t *reg, uint32_t mask,
                               uint32_t shift, uint32_t value) {
  *reg = (*reg & ~mask) | ((value << shift) & mask);
}

static inline bool bit_is_set(uint32_t reg, uint32_t bit_num) {
  return (reg & bit(bit_num)) != 0;
}

static inline void bit_set(volatile uint32_t *reg, uint32_t bit_num) {
  *reg |= bit(bit_num);
}

static inline void bit_clear(volatile uint32_t *reg, uint32_t bit_num) {
  *reg &= ~bit(bit_num);
}

static inline void bit_toggle(volatile uint32_t *reg, uint32_t bit_num) {
  *reg ^= bit(bit_num);
}

void delay_cycles(uint32_t cycles);

#endif /* COMMON_H */
