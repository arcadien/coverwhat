#pragma once

#include "Action.h"
#include "Actor.h"

namespace Meta
{
  
  struct Entities
  {
    static const int Health = 0x0;
  };

  struct Actions{

    static const Action DAMAGE5;

    static const Action HEAL5;

  };

  const Action Actions::DAMAGE5 = Action(Action::Type::DAMAGE, Meta::Entities::Health, Action::Amount::AMOUNT_5, 30);
  const Action Actions::HEAL5 = Action(Action::Type::HEAL, Meta::Entities::Health, Action::Amount::AMOUNT_5, 30);
}
