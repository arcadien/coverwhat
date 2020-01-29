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

#if defined(AVR)

#include <Arduino.h>
#include <api/IUi.h>

#include <api/Action.h>
#include <api/Entity.h>
class Entity;

namespace {

/*!
 * Sends necessary content to Bluetooth Electronic
 * app to let it display our UI
 */
void DrawUi() {
  Serial.println("*.kwl");
  Serial.println("clear_panel()");
  Serial.print("set_grid_size(10,5)");
  Serial.println("");
  Serial.print("add_text(0,0,large,L");
  Serial.print(",Health,245,240,245,");
  Serial.println(")");
  Serial.print("add_text(0,4,large,L");
  Serial.print(",Hero,245,240,245,)");
  Serial.println("");
  Serial.print("add_text(0,1,large,L");
  Serial.print(",Ammo,245,240,245,)");
  Serial.println("");
  Serial.print("add_text(0,3,large,L");
  Serial.print(",Spawns,245,240,245,");
  Serial.println(")");
  Serial.print("add_text_box(2,3,1,L");
  Serial.print(",\"\\n \",245,240,245,S");
  Serial.println(")");
  Serial.print("add_text_box(2,4,4,L");
  Serial.println(",,245,240,245,E)");
  Serial.print("add_button(6,4,9,C,c");
  Serial.println(")");
  Serial.print("add_button(8,3,29,R,");
  Serial.println("r)");
  Serial.print("add_gauge(2,0,4,0,50");
  Serial.println("0,0,L,,l,5,0)");
  Serial.print("add_gauge(2,1,5,0,10");
  Serial.println("0,100,A,,,10,10)");
  Serial.print("add_buzzer(9,0,1,D,a");
  Serial.println(",true,100.00)");
  Serial.print("add_buzzer(9,1,1,H,b");
  Serial.println(",false,100.00)");
  Serial.print("add_buzzer(9,2,1,M,c");
  Serial.println(",false,100.00)");
  Serial.print("set_panel_notes(,,,)");
  Serial.println("");
  Serial.println("run()");
  Serial.println("*");
}

} // namespace

namespace ui {

class BluetoothElectronicUi : public IUi {
public:
  BluetoothElectronicUi(int baudrate) {
    Serial.begin(baudrate);
    DrawUi();
  }
  bool ActionAvailable() const override { return false; }
  Action GetAction() const override { return Action(); }
  void DisplayDied() const override {}
  void Display(Entity const &entity) const override {}
  void Print(char const *message) const override { Serial.println(message); }
};
} // namespace ui

#endif
