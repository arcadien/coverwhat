
#pragma once

#include "Hardware.h"
#include <thread>
#include <chrono>

namespace hardware
{
/*
 * This class implement a mock hardware
*/
class Simulated{
  public:
    void sleepMs(uint8_t ms){
      using namespace std::chrono_literals;
      auto duration = std::chrono::milliseconds(ms);
      std::this_thread::sleep_for(duration);
    }
};
}
