#pragma once
#include <stdint.h>

namespace streetlight {
// For 5V -> LDR -> A0 -> 10k -> GND: darkness produces a lower ADC value.
inline bool updateNight(bool night, uint16_t light, uint16_t enterNight,
                        uint16_t enterDay) {
  if (!night && light <= enterNight) return true;
  if (night && light >= enterDay) return false;
  return night;
}
inline bool holdActive(bool seen, uint32_t now, uint32_t lastSeen,
                       uint32_t holdMs) {
  return seen && uint32_t(now - lastSeen) < holdMs;
}
inline uint8_t brightness(bool night, bool active, uint8_t dim,
                          uint8_t bright) {
  return night ? (active ? bright : dim) : 0;
}
}  // namespace streetlight
