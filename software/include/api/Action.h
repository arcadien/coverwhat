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

#include <api/IAction.h>
/*!
   A Message is composed of 11 bits.

     10 9 8 7     6 5 4   3 2 1    0
   |----------- | ----- | ----- | --- |
      source       type   amnt    sum
*/

class Action : public IAction {
 public:
  Action()
      : _type(Type::NONE),
        _entityTag(Entity::Tag::None),
        _amount(Action::Amount::AMOUNT_0),
        _coolDown(0) {}

  Action(Type const &type, Entity::Tag const &entityTag, Amount const &amount,
         uint8_t cooldown)
      : _type(type),
        _entityTag(entityTag),
        _amount(amount),
        _coolDown(cooldown) {}

  Entity::Tag const &GetTargetEntityTag() const override { return _entityTag; }

  Amount GetAmount() const override { return _amount; }

  uint8_t GetCoolDownMs() const override { return _coolDown; }

  uint16_t Process(uint16_t currentValue) const override {
    uint16_t result = currentValue;
    switch (_type) {
      case (IAction::Type::DAMAGE):
        if ((uint16_t)_amount > result) {
          result = 0;
        } else {
          result -= (uint16_t)_amount;
        }
        break;
      case (IAction::Type::HEAL):
        result += (uint16_t)_amount;
        break;
      case (IAction::Type::RESURRECT):
      case (IAction::Type::NONE):
        break;
    }
    return result;
  }

 private:
  Type _type;
  Entity::Tag _entityTag;
  Amount _amount;
  uint8_t _coolDown;
};

