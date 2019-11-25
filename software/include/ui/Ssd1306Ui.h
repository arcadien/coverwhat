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

#include <api/IUi.h>

namespace ui {
class Ssd1306 : public IUi {
 public:
  
  Ssd1306();

  bool ActionAvailable() const override { return false; }
  Action GetAction() const override { return Action(); }
  void DisplayDied() const override {}
  void Display(Entity const &entity) const override;
  void Print(char const *message) const override{};

};
}  // namespace ui
