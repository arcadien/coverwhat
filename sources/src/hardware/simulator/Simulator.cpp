#include <hardware/simulator/Simulator.h>
#include <numeric>
#include <thread>

namespace hardware {
void Simulator::sleepMs(uint8_t ms) {
  auto duration = std::chrono::milliseconds(ms);
  std::this_thread::sleep_for(duration);
}

void Simulator::Stop(){ _stop = true;}

void Simulator::Setup() {
  _epoch = std::chrono::high_resolution_clock::now();

  auto ClockFunction = [this]() {
    while (!_stop) {
      std::this_thread::sleep_for(std::chrono::milliseconds(10));
      OnTick();
    }
  };
  std::thread t(ClockFunction);
  t.detach();
}

/*
 *
 * This implementation reproduce the ATmega328p
 * behavior: milliseconds are stored in a `unsigned long`
 * which mean the clock will overflow to 0 roughly each 50 days
 *
 */
unsigned long Simulator::Millis() {
  unsigned long result = 0;
  auto now = std::chrono::high_resolution_clock::now();
  auto elapsed = now - _epoch;
  long long ms =
      std::chrono::duration_cast<std::chrono::milliseconds>(elapsed).count();
  if (ms >= std::numeric_limits<unsigned long>::max()) {
    _epoch = now;
  } else {
    result = static_cast<unsigned long>(ms);
  }
  return result;
}

void Simulator::OnPrimaryAction() {}
void Simulator::OnSecondaryAction() {}
void Simulator::OnTick() {}

} // namespace hardware
