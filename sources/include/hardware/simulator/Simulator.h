
#pragma once

#include <api/IHardware.h>
#include <chrono>
#include <memory>
#include <thread>
#include <mutex>

namespace hardware {
/*
 * This class implement a simulated hardware which run on a regular PC
 *
 * This hardware will help developing logic outside the complexity of a real
 * hardware target.
 */
class Simulator : public IHardware {
public:
  
  Simulator() : _stop(false){}

  void sleepMs(uint8_t ms) override;
  void Setup() override;
  unsigned long Millis() override;
  void OnPrimaryAction() override;
  void OnSecondaryAction() override;
  void OnTick() override;
  void Stop() override;

private:
  std::shared_ptr<std::thread> _millisCounter;
  std::chrono::steady_clock::time_point _epoch;
  bool _stop;
};
} // namespace hardware
