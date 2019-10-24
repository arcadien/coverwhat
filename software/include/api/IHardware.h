#pragma once

#include <stdint.h>
namespace hardware {

/*
 * Hardware abstraction layer
 *
 */
class IHardware {
 public:
  static const int TICK_INTERVAL_MS = 10;

  virtual ~IHardware() = default;

  /*
   * Blocking call: during the sleep time, nothing but interrupt can occur
   */
  virtual void sleepMs(uint16_t ms) = 0;

  virtual void Stop() = 0;

  /*
   * Trigger low-level initialization of
   * the hardware layer, and must be called
   * as soon as possible after software starts.
   */
  virtual void Setup() = 0;

  /*
   * Return number of milliseconds lasted since
   * last call of Setup().
   * Continuously, this counter will overflow to zero
   * after around 50 days.
   */
  virtual unsigned long Millis() = 0;

  virtual void OnPrimaryAction() = 0;
  virtual void OnSecondaryAction() = 0;

  /* The hardware provide a clock, which call
   * OnTick() at regular interval.
   *
   */
  virtual void OnTick() = 0;

  /*!
   * Hardware comes here at the end of event loop.
   * This is the place to implement a busy-wait delay
   * or a sleep mode, if an interrupt is likely to wake the
   * hardware up
   */
  virtual void WaitForEvent() = 0;
};
}  // namespace hardware