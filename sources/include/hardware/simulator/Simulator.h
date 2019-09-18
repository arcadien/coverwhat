
#pragma once

#include <api/IHardware.h>

namespace hardware
{
/*
 * This class implement a simulated hardware which run on a regular PC
 * 
 * This hardware will help developing logic outside the complexity of a real hardware target.
*/
class Simulator : public IHardware{
  public:
    void sleepMs(uint8_t ms) override;
};
}
