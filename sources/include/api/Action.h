#pragma once

#include <api/Entity.h>
#include <stdint.h>

/*!
   A Message is composed of 11 bits.

     10 9 8 7     6 5 4   3 2 1    0
   |----------- | ----- | ----- | --- |
      source       type   amnt    sum
*/

/**
 * A Action represent an atomic intent of alteration for an Actor Entity
 *
 * Ex. A damage Action may target a 'health' Entity, for a value of 24.
 *
 * Sometimes an Action cannot be repeated instantly. The delay between each
 * action trigger is called 'cooldown' and is expressed as a duration in
 * milliseconds.
 */
class Action {
 public:
  /*
   * Initial value which can take an Action
   *
   *
   */
  enum class Amount : uint8_t {
    AMOUNT_0 = 0,
    AMOUNT_1 = 1,
    AMOUNT_5 = 5,
    AMOUNT_10 = 10,
    AMOUNT_25 = 25,
    AMOUNT_50 = 50,
    AMOUNT_100 = 100,
    AMOUNT_250 = 250,
    AMOUNT_FULL = 255
  };

  enum Type { DAMAGE, HEAL, STUN, RESURRECT, NONE };

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

  Entity::Tag const &GetTargetEntityTag() const { return _entityTag; }

  Amount GetAmount() const { return _amount; }

  uint8_t GetCoolDownMs() const { return _coolDown; }

  uint16_t Process(uint16_t currentValue) const {
    uint16_t result = currentValue;
    switch (_type) {
      case (DAMAGE):
        result -= (uint16_t)_amount;
        break;
      case (HEAL):
        result += (uint16_t)_amount;
        break;
      case (RESURRECT):
      case (STUN):
      case (NONE):
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

