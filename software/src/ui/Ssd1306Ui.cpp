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

#include <api/Action.h>
#include <ui/Ssd1306Ui.h>

#include <ssd1306.h>


namespace ui {

Ssd1306::Ssd1306()
{
  ssd1306_setFixedFont(ssd1306xled_font6x8);
  ssd1306_128x32_i2c_init();
  ssd1306_clearScreen();
}

  void Ssd1306::Display(Entity const &entity) const
  {
    ssd1306_setFixedFont(ssd1306xled_font6x8);
    ssd1306_printFixedN(0, 5, String(entity.GetValue()).c_str(), STYLE_NORMAL, 2);
  }

};