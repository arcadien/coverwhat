#pragma once

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
 * Ex. A damage action may target a 'health' entity, for a value of 24.
 *
 * Sometimes an action cannot be repeated instantly. The delay between each action
 * trigger is called 'cooldown' and is expressed as a duration in milliseconds.
 */
class Action{

  public:

    /*
     * Initial value which can take an Action
     *
     *
     */
    enum Amount {
    AMOUNT_1,
    AMOUNT_5,
    AMOUNT_10,
    AMOUNT_25,
    AMOUNT_50,
    AMOUNT_100,
    AMOUNT_250,
    AMOUNT_FULL
  };

  enum Type{
    DAMAGE,
    HEAL,
  };

    Action(Type const& type, uint8_t entityTag, Amount const& amount, uint8_t cooldown):
      _entityTag(entityTag), _amount(amount), _coolDown(cooldown) {}

    uint8_t GetTargetEntityTag()
    {
      return _entityTag;
    }  

    uint8_t GetAmount(){
      return _amount;
    }
    
    uint8_t GetCoolDownMs()
    {
      return _coolDown;
    }

  private:
    uint8_t _entityTag;
    uint8_t _coolDown;
    Type _type;
    Amount _amount;

};
