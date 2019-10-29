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
}  // namespace Meta
