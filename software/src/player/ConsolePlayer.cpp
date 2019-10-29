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

#include <actors/Player.h>
#include <hardware/simulator/Simulator.h>
#include <tools/RGBColor.h>
#include <ui/ConsoleUi.h>
#include <iostream>
#include <thread>

ui::ConsoleUi userInterface(std::cin);
actors::Player player;
RGBColor rgbColor;
hardware::Simulator hw;

namespace {
long map(long x, long in_min, long in_max, long out_min, long out_max) {
  return (x - in_min) * (out_max - out_min) / (in_max - in_min) + out_min;
}

}  // namespace

void setup() {}

void loop() {
  if (userInterface.ActionAvailable()) {
    player.Accept(userInterface.GetAction());
    userInterface.Display(player.GetEntity(Entity::Tag::Health));
    int hue = map(player.GetEntityValue(Entity::Tag::Health), 0, 200, 0, 145);
    rgbColor.FromHSV(hue, 255, 255);
  }
}

int main(int, char**) {
  setup();
  for (;;) {
    loop();
    // busy wait sleep
    hw.sleepMs(10);
  }
}
