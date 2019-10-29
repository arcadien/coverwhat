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

#include <api/Entity.h>
#include <stdint.h>

/**
 * A IAction represent an atomic intent of alteration for an Actor Entity
 *
 * Ex. A damage Action may target a 'health' Entity, for a value of 24.
 *
 * Sometimes an Action cannot be repeated instantly. The delay between each
 * action trigger is called 'cooldown' and is expressed as a duration in
 * milliseconds.
 */
class IAction {
 public:
  enum class Amount : uint8_t {
    AMOUNT_0 = 0,
    AMOUNT_1 = 1,
    AMOUNT_5 = 5,
    AMOUNT_10 = 10,
    AMOUNT_25 = 25,
    AMOUNT_50 = 50,
    AMOUNT_100 = 100,
    AMOUNT_250 = 250
  };

  enum class Type : char {
    DAMAGE = 'D',
    HEAL = 'H',
    /* STUN='S',*/
    RESURRECT = 'R',
    NONE = 'N',
  };

  virtual Entity::Tag const& GetTargetEntityTag() const = 0;
  virtual Amount GetAmount() const = 0;
  virtual uint8_t GetCoolDownMs() const = 0;
  virtual uint16_t Process(uint16_t currentValue) const = 0;
};

