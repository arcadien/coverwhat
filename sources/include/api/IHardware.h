#pragma once

#include <stdint.h>
namespace hardware {
/*
 * Hardware abstraction layer
 */
class IHardware {
public:
  IHardware() noexcept;
  virtual ~IHardware() = default;
  virtual void sleepMs(uint8_t ms) = 0;
};
} // namespace hardware
