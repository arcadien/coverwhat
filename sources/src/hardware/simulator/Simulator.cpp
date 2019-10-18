#include <hardware/simulator/Simulator.h>
#include <numeric>
#include <thread>

#include <chrono>
#include <mutex>

namespace hardware {
void Simulator::sleepMs(uint8_t ms) {
  auto duration = std::chrono::milliseconds(ms);
  std::this_thread::sleep_for(duration);
}

void Simulator::Stop() { _clock.stop(); }

void Simulator::Setup() {
  _primaryActionExecutionCount = 0;
  _secondaryActionExecutionCount = 0;

  _epoch = std::chrono::system_clock::now().time_since_epoch() /
           std::chrono::milliseconds(1);

  _clock.setInterval(
      [this]() {
        std::lock_guard<std::mutex> guard(_mutex);
        OnTick();
      },
      10);
}

/*
 *
 * This implementation reproduce the ATmega328p
 * behavior: milliseconds are stored in a `unsigned long`
 * which mean the clock will overflow to 0 roughly each 50 days
 *
 */
unsigned long Simulator::Millis() {
  unsigned long result;

  unsigned long long milliseconds_since_epoch =
      std::chrono::system_clock::now().time_since_epoch() /
      std::chrono::milliseconds(1);

  unsigned long long elapsed = milliseconds_since_epoch - _epoch;

  if (elapsed >= std::numeric_limits<unsigned long>::max()) {
    _epoch = milliseconds_since_epoch;
    result = 0;
  } else {
    result = static_cast<unsigned long>(milliseconds_since_epoch);
  }
  return result;
}

long Simulator::PrimaryActionCount() { return _primaryActionExecutionCount; }

long Simulator::SecondaryActionCount() {
  return _secondaryActionExecutionCount;
}

void Simulator::TriggerPrimaryAction() {
  _primaryActionExecutionCount++;
  OnPrimaryAction();
}
void Simulator::TriggerSecondaryAction() {
  _secondaryActionExecutionCount++;
  OnSecondaryAction();
}

void Simulator::OnPrimaryAction() {}
void Simulator::OnSecondaryAction() {}
void Simulator::OnTick() {}

}  // namespace hardware
