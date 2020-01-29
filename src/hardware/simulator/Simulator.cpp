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

#include <hardware/simulator/Simulator.h>

#include <chrono>
#include <mutex>
#include <numeric>
#include <thread>

namespace {
void SleepInMs(uint64_t ms) {
  struct timespec ts;
  ts.tv_sec = ms / 1000;
  ts.tv_nsec = ms % 1000 * 1000000;

  while (nanosleep(&ts, &ts) == -1 && errno == EINTR)
    ;
}

uint64_t NowInMs() {
  struct timespec now;
  clock_gettime(CLOCK_MONOTONIC, &now);
  return static_cast<uint64_t>(now.tv_sec * 1000 + now.tv_nsec / 1000000);
}

}  // namespace

namespace hardware {

Simulator::Simulator(unsigned long initialMillis)
    : _millis(NowInMs()),
      _primaryActionExecutionCount(0),
      _secondaryActionExecutionCount(0) {
  Setup();
}

Simulator::~Simulator() { Stop(); }

void Simulator::sleepMs(uint16_t ms) { SleepInMs(ms); }

void Simulator::WaitForEvent() {
  SleepInMs(static_cast<uint16_t>(2 * TICK_INTERVAL_MS));
}

void Simulator::Stop() {
  _tickClock.Stop();
  // wait for threads to actually stop
  auto delay = std::chrono::milliseconds(200);
  std::this_thread::sleep_for(delay);
}

void Simulator::Setup() {
  _primaryActionExecutionCount = 0;
  _secondaryActionExecutionCount = 0;
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
unsigned long Simulator::Millis() { return NowInMs() - _millis; }

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
