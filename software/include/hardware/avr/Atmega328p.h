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

#pragma once

#include <api/IHardware.h>

namespace hardware {
/*
 * This class implement IHarware for a ATMega328P chip
 *
 */
class Atmega328p : public IHardware {
 public:
  void sleepMs(uint16_t ms) override {}
  void Setup() override {}
  unsigned long Millis() override { return 0; }
  void OnPrimaryAction() override {}
  void OnSecondaryAction() override {}
  void OnTick() override {}
  void Stop() override {}
  void WaitForEvent() override {}
};
}  // namespace hardware
