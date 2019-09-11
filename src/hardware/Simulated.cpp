#include <hardware/Simulated.h>
#include <chrono>
#include <thread>

namespace hardware
{
  void Simulated::sleepMs(uint8_t ms) {
      auto duration = std::chrono::milliseconds(ms);
      std::this_thread::sleep_for(duration);
  }
  
}
