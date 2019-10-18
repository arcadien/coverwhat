
#pragma once

#include <api/IHardware.h>

#include <chrono>
#include <future>
#include <memory>
#include <mutex>
#include <thread>

namespace hardware {

class Timer {
  bool clear = false;

 public:
  template <typename Function>
  void setTimeout(Function function, int delay) {
    this->clear = false;
    std::thread t([=]() {
      if (this->clear) return;
      std::this_thread::sleep_for(std::chrono::milliseconds(delay));
      if (this->clear) return;
      function();
    });
    t.detach();
  }

  template <typename Function>
  void setInterval(Function function, int interval) {
    this->clear = false;
    std::thread t([=]() {
      while (true) {
        if (this->clear) return;
        std::this_thread::sleep_for(std::chrono::milliseconds(interval));
        if (this->clear) return;
        function();
      }
    });
    t.detach();
  }
  void stop() { this->clear = true; }
};

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
  hardware::Timer _clock;
  std::shared_ptr<std::thread> _millisCounter;
  long long _epoch;
  long _primaryActionExecutionCount;
  long _secondaryActionExecutionCount;
  std::mutex _mutex;
};
}  // namespace hardware
