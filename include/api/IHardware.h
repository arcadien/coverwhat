/*
 * This file is part of the Hack distribution (https://github.com/arcadien/Hack)
 *
 * Copyright (c) 2019 Aurélien Labrosse
 *
 * This program is free software: you can redistribute it and/or modify
 * it under the terms of the GNU General Public License as published by
 * the Free Software Foundation, version 3.
 *
 * This program is distributed in the hope that it will be useful, but
 * WITHOUT ANY WARRANTY; without even the implied warranty of
 * MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE. See the GNU
 * General Public License for more details.
 *
 * You should have received a copy of the GNU General Public License
 * along with this program. If not, see <http://www.gnu.org/licenses/>.
 */

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
} // namespace hardware
