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

#include <api/IHardware.h>
#include <tools/Timer.h>

#include <chrono>
#include <future>
#include <memory>
#include <mutex>
#include <thread>

namespace hardware {

/*
 * This class implement a simulated hardware which run on a regular PC
 *
 * This hardware will help developing logic outside the complexity of a real
 * hardware target.
 */
class Simulator : public IHardware {
 public:
  Simulator(unsigned long initialMillis = 0);
  virtual ~Simulator();
  void sleepMs(uint16_t ms) override;
  void Setup() override;
  unsigned long Millis() override;
  void OnPrimaryAction() override;
  void OnSecondaryAction() override;
  void Stop() override;
  virtual void OnTick() override;
  void WaitForEvent() override;

  /*!
   * How many times the primary action has been
   * triggered since last Setup()
   */
  long PrimaryActionCount();

  /*!
   * How many times the secondary action has been
   * triggered since last Setup()
   */
  long SecondaryActionCount();

  void TriggerPrimaryAction();
  void TriggerSecondaryAction();

 private:
  tools::Timer _tickClock;
  uint64_t _millis;
  long _primaryActionExecutionCount;
  long _secondaryActionExecutionCount;
  std::mutex _tickMutex;
};
}  // namespace hardware
