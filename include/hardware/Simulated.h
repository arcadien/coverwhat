
#pragma once

#include "IHardware.h"

namespace hardware
{
/*
 * This class implement a mock hardware
*/
class Simulated : public IHardware{
  public:
    void sleepMs(uint8_t ms) override;
};
}
