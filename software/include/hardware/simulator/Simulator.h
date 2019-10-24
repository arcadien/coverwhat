
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
  Simulator(unsigned long initialMillis = 0);
  virtual ~Simulator();
  void sleepMs(uint16_t ms) override;
  void Setup() override;
  unsigned long Millis() override;
  void OnPrimaryAction() override;
  void OnSecondaryAction() override;
  void Stop() override;
  virtual void OnTick() override;
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
  tools::Timer _millisClock;
  tools::Timer _tickClock;
  unsigned long _millis;
  long _primaryActionExecutionCount;
  long _secondaryActionExecutionCount;
  std::mutex _tickMutex;
  std::mutex _millisMutex;
};
}  // namespace hardware
