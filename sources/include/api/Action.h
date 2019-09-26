#pragma once

#include <stdint.h>

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

    Action(uint8_t entityTag, uint8_t value, uint8_t cooldown):
      _entityTag(entityTag), _value(value), _coolDown(cooldown) {}

    uint8_t GetTargetEntityTag()
    {
      return _entityTag;
    }  

    uint8_t GetValue(){
      return _value;
    }
    
    uint8_t GetCoolDownMs()
    {
      return _coolDown;
    }

  private:
    uint8_t _entityTag;
    uint8_t _value;
    uint8_t _coolDown;
};
