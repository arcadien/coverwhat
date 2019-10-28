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

