#include <hardware/simulator/Simulator.h>
#include <numeric>
#include <thread>

#include <chrono>
#include <mutex>

namespace hardware {

Simulator::Simulator(unsigned long initialMillis)
    : _millis(initialMillis),
      _primaryActionExecutionCount(0),
      _secondaryActionExecutionCount(0) {
  Setup();
}

Simulator::~Simulator() { Stop(); }

void Simulator::sleepMs(uint16_t ms) {
  auto duration = std::chrono::milliseconds(ms);
  std::this_thread::sleep_for(duration);
}

void Simulator::WaitForEvent() {
  std::this_thread::sleep_for(std::chrono::milliseconds(2 * TICK_INTERVAL_MS));
}

void Simulator::Stop() {
  _millisClock.Stop();
  _tickClock.Stop();
  // wait for thread to actually stop, wait
  // for tick duration at least so that Timer loop
  // will end
  auto delay = std::chrono::milliseconds(TICK_INTERVAL_MS);
  std::this_thread::sleep_for(delay);
}

void Simulator::Setup() {
  _primaryActionExecutionCount = 0;
  _secondaryActionExecutionCount = 0;

  _millisClock.SetInterval(
      [=]() {
        static const unsigned long max =
            std::numeric_limits<unsigned long>::max();
        if (_millis < max) {
          std::lock_guard<std::mutex> guard(_millisMutex);
          ++_millis;
        } else {
          std::lock_guard<std::mutex> guard(_millisMutex);
          _millis = 0;
        }
      },
      1);

  _tickClock.SetInterval(
      [=]() {
        std::lock_guard<std::mutex> guard(_tickMutex);
        this->OnTick();
      },
      TICK_INTERVAL_MS);
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
  std::lock_guard<std::mutex> guard(_millisMutex);
  return _millis;
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
