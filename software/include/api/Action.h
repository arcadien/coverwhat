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
      case (DAMAGE):
        result -= (uint16_t)_amount;
        break;
      case (HEAL):
        result += (uint16_t)_amount;
        break;
      case (RESURRECT):
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

