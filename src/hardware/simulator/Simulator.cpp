#include <hardware/simulator/Simulator.h>
#include <chrono>
#include <thread>

namespace hardware
{
  void Simulator::sleepMs(uint8_t ms) {
      auto duration = std::chrono::milliseconds(ms);
      std::this_thread::sleep_for(duration);
  }
}
