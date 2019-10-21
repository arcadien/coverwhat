
#pragma once

#include <api/IHardware.h>

namespace hardware {
/*
 * This class implement IHarware for a ATMega328P chip
 *
 */
class Atmega328p : public IHardware {
 public:
  void sleepMs(uint8_t ms) override {}
  void Setup() override {}
  unsigned long Millis() override { return 0; }
  void OnPrimaryAction() override {}
  void OnSecondaryAction() override {}
  void OnTick() override {}
  void Stop() override {}
  void WaitForEvent() override {}
};
}  // namespace hardware
