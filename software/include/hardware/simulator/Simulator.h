
#pragma once

#include <api/IHardware.h>
#include <tools/Timer.h>

#include <chrono>
#include <future>
#include <memory>
#include <mutex>
#include <thread>

namespace hardware {

/*
 * This class implement a simulated hardware which run on a regular PC
 *
 * This hardware will help developing logic outside the complexity of a real
 * hardware target.
 */
class Simulator : public IHardware {
 public:
  Simulator()
      : _epoch(0),
        _primaryActionExecutionCount(0),
        _secondaryActionExecutionCount(0) {}

  void sleepMs(uint8_t ms) override;
  void Setup() override;
  unsigned long Millis() override;
  void OnPrimaryAction() override;
  void OnSecondaryAction() override;
  void OnTick() override;
  void Stop() override;
  void WaitForEvent() override;

  /*!
   * How many times the primary action has been
   * triggered since last Setup()
   */
  long PrimaryActionCount();

  /*!
   * How many times the secondary action has been
   * triggered since last Setup()
   */
  long SecondaryActionCount();

  void TriggerPrimaryAction();
  void TriggerSecondaryAction();

 private:
  tools::Timer _clock;
  std::shared_ptr<std::thread> _millisCounter;
  long long _epoch;
  long _primaryActionExecutionCount;
  long _secondaryActionExecutionCount;
  std::mutex _mutex;
};
}  // namespace hardware
