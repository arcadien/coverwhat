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

#include <api/Action.h>
#include <api/Entity.h>
#include <api/Team.h>

namespace actors {
class Player {
 public:
  Player(uint16_t initialHealth)
      : _initialHealth(Entity::Tag::Health, initialHealth),
        _health(Entity::Tag::Health, initialHealth),
        _team(Team::None) {}

  Player(uint16_t initialHealth, Team const &team)
      : _initialHealth(Entity::Tag::Health, initialHealth),
        _health(Entity::Tag::Health, initialHealth),
        _team(team) {}

  Team const &GetTeam() { return _team; }

  void Accept(Action const &action) {
    if (IAction::Type::RESURRECT == action.GetType()) {
      _health = _initialHealth;
    } else {
      uint16_t newValue = action.Process(_health.GetValue());
      _health.SetValue(newValue);
    }
  }

  Entity const &GetHealth() { return _health; }

 private:
  void SetHealth(uint16_t value) { _health.SetValue(value); }
  Entity _health;
  Entity _initialHealth;
  const Team _team;
};
}  // namespace actors

