#pragma once

#include "Action.h"
#include "Actor.h"
#include "Entity.h"

/*!
 * Meta namespace contain information shared across concepts (eg. Player,
 * Weapon) which are not necessarily implemented as the same place, but have to
 * exchange the only needed information.
 */
namespace Meta {

struct Actions {
  static const Action DAMAGE5;
  static const Action HEAL5;
};

const Action Actions::DAMAGE5 = Action(
    Action::Type::DAMAGE, Entity::Tag::Health, Action::Amount::AMOUNT_5, 30);
const Action Actions::HEAL5 = Action(Action::Type::HEAL, Entity::Tag::Health,
                                     Action::Amount::AMOUNT_5, 30);
} // namespace Meta
