/*
 * This file is part of the KOTH distribution (https://github.com/arcadien/koth)
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

#include <hardware/simulator/Simulator.h>
#include <numeric>
#include <thread>

#include <chrono>
#include <mutex>

namespace hardware {

Simulator::Simulator(unsigned long initialMillis)
    : _millis(initialMillis),
      _primaryActionExecutionCount(0),
      _secondaryActionExecutionCount(0) {
  Setup();
}

Simulator::~Simulator() { Stop(); }

void Simulator::sleepMs(uint16_t ms) {
  auto duration = std::chrono::milliseconds(ms);
  std::this_thread::sleep_for(duration);
}

void Simulator::WaitForEvent() {
  std::this_thread::sleep_for(std::chrono::milliseconds(2 * TICK_INTERVAL_MS));
}

void Simulator::Stop() {
  _millisClock.Stop();
  _tickClock.Stop();
  
  // wait for threads to actually stop
  auto delay = std::chrono::milliseconds(TICK_INTERVAL_MS);

  std::this_thread::sleep_for(delay);
}

void Simulator::Setup() {
  _primaryActionExecutionCount = 0;
  _secondaryActionExecutionCount = 0;

  _millisClock.SetInterval(
      [=]() {
        static const unsigned long max =
            std::numeric_limits<unsigned long>::max();
        if (_millis < max) {
          std::lock_guard<std::mutex> guard(_millisMutex);
          ++_millis;
        } else {
          std::lock_guard<std::mutex> guard(_millisMutex);
          _millis = 0;
        }
      },
      1);

  _tickClock.SetInterval(
      [=]() {
        std::lock_guard<std::mutex> guard(_tickMutex);
        this->OnTick();
      },
      TICK_INTERVAL_MS);
}

/*
 *
 * This implementation reproduce the ATmega328p
 * behavior: milliseconds are stored in a `unsigned long`
 * which mean the clock will overflow to 0 roughly each 50 days
 *
 */
unsigned long Simulator::Millis() {
  std::lock_guard<std::mutex> guard(_millisMutex);
  return _millis;
}

long Simulator::PrimaryActionCount() { return _primaryActionExecutionCount; }

long Simulator::SecondaryActionCount() {
  return _secondaryActionExecutionCount;
}

void Simulator::TriggerPrimaryAction() {
  _primaryActionExecutionCount++;
  OnPrimaryAction();
}
void Simulator::TriggerSecondaryAction() {
  _secondaryActionExecutionCount++;
  OnSecondaryAction();
}

void Simulator::OnPrimaryAction() {}
void Simulator::OnSecondaryAction() {}
void Simulator::OnTick() {}

}  // namespace hardware
