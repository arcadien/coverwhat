/*
 * This file is part of the Hack distribution (https://github.com/arcadien/Hack)
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

class Action;
class Entity;

namespace ui {

class IUi {
public:
  virtual bool ActionAvailable() const = 0;
  virtual Action GetAction() const = 0;
  virtual void DisplayDied() const = 0;
  virtual void Display(Entity const &entity) const = 0;
  virtual void Print(char const *message) const = 0;
};

} // namespace ui
