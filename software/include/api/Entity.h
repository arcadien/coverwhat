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

#include <stdint.h>

class Entity {
 public:
  enum class Tag : const uint16_t { None = 0x0, Health = 0x1 };

  Entity(Tag const& tag, uint16_t initialValue)
      : _tag(tag), _initialValue(initialValue), _currentValue(initialValue) {}

  Tag const& GetTag() const { return _tag; }

  uint16_t GetValue() const { return _currentValue; }
  void SetValue(uint16_t value) {
    if (value > _initialValue) {
      _currentValue = _initialValue;
    } else {
      _currentValue = value;
    }
  }

 private:
  Tag _tag;
  uint16_t _initialValue;
  uint16_t _currentValue;
};
