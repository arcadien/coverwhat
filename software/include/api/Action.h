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
class Action : public IAction {
 public:
  /*!
     A Message is composed of 11 bits.

     Unsigned long

     |--------|--------|--------|--------|

       10 9 8 7     6 5 4   3 2 1    0
     |----------- | ----- | ----- | --- |
        source       type   amnt    sum
  */
  Action(IAction::CompactType const &compactRepresentation) {
    CompactType damageMask = 0x10;  // 0b0010000
    CompactType healMask = 0x20;    // 0b0100000

    CompactType amount1mask = 0x2;    // 0b0010
    CompactType amount5mask = 0x4;    // 0b0100
    CompactType amount10mask = 0x6;   // 0b0110
    CompactType amount25mask = 0x8;   // 0b1000
    CompactType amount50mask = 0xA;   // 0b1010
    CompactType amount100mask = 0xC;  // 0b1100
    CompactType amount250mask = 0xE;  // 0b1110

    if ((compactRepresentation & amount1mask) == amount1mask) {
      _amount = IAction::Amount::AMOUNT_1;

    } else if ((compactRepresentation & amount5mask) == amount5mask) {
      _amount = IAction::Amount::AMOUNT_5;

    } else if ((compactRepresentation & amount10mask) == amount10mask) {
      _amount = IAction::Amount::AMOUNT_10;

    } else if ((compactRepresentation & amount25mask) == amount25mask) {
      _amount = IAction::Amount::AMOUNT_25;

    } else if ((compactRepresentation & amount50mask) == amount50mask) {
      _amount = IAction::Amount::AMOUNT_50;

    } else if ((compactRepresentation & amount100mask) == amount100mask) {
      _amount = IAction::Amount::AMOUNT_100;

    } else if ((compactRepresentation & amount250mask) == amount250mask) {
      _amount = IAction::Amount::AMOUNT_250;

    } else {
      _amount = IAction::Amount::AMOUNT_0;
    }

    if ((compactRepresentation & damageMask) == damageMask) {
      _type = IAction::Type::DAMAGE;

    } else if ((compactRepresentation & healMask) == healMask) {
      _type = IAction::Type::HEAL;

    } else {
      _type = IAction::Type::NONE;
    }
  }

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

  CompactType Compact() {
    CompactType result = 0;

    return result;
  }

  Type const &GetType() const override { return _type; }

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

