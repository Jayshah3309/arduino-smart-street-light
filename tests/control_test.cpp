#include "../firmware/smart_street_light/control.h"
#include <assert.h>
#include <iostream>
using namespace streetlight;
int main() {
  assert(updateNight(false, 350, 350, 450));
  assert(!updateNight(false, 351, 350, 450));
  assert(updateNight(true, 449, 350, 450));
  assert(!updateNight(true, 450, 350, 450));
  assert(!holdActive(false, 0, 0, 3000));
  assert(holdActive(true, 3999, 1000, 3000));
  assert(!holdActive(true, 4000, 1000, 3000));
  assert(holdActive(true, 10, UINT32_MAX - 9, 3000));
  assert(!holdActive(true, 2990, UINT32_MAX - 9, 3000));
  assert(brightness(false, true, 40, 255) == 0);
  assert(brightness(false, false, 40, 255) == 0);
  assert(brightness(true, false, 40, 255) == 40);
  assert(brightness(true, true, 40, 255) == 255);
  const bool active[3] = {true, false, true};
  const uint8_t expected[3] = {255, 40, 255};
  for (int i = 0; i < 3; ++i)
    assert(brightness(true, active[i], 40, 255) == expected[i]);
  std::cout << "Control logic tests passed\n";
}
