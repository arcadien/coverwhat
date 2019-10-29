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

#include <stdint.h>

#if defined(AVR)
#include <avr/pgmspace.h>
#else
#define PROGMEM
#endif

/*
 * Stores uint8 value for red, green and blue value for a color
 *
 */
struct RGBColor {
  int red;
  int green;
  int blue;

  /*
   * Correction table used for HSV value and saturation (inverted) to obtain
   * more natural colors
   */
  const PROGMEM uint8_t dim_curve[256]{
      0,   1,   1,   2,   2,   2,   2,   2,   2,   3,   3,   3,   3,   3,   3,
      3,   3,   3,   3,   3,   3,   3,   3,   4,   4,   4,   4,   4,   4,   4,
      4,   4,   4,   4,   4,   5,   5,   5,   5,   5,   5,   5,   5,   5,   5,
      6,   6,   6,   6,   6,   6,   6,   6,   7,   7,   7,   7,   7,   7,   7,
      8,   8,   8,   8,   8,   8,   9,   9,   9,   9,   9,   9,   10,  10,  10,
      10,  10,  11,  11,  11,  11,  11,  12,  12,  12,  12,  12,  13,  13,  13,
      13,  14,  14,  14,  14,  15,  15,  15,  16,  16,  16,  16,  17,  17,  17,
      18,  18,  18,  19,  19,  19,  20,  20,  20,  21,  21,  22,  22,  22,  23,
      23,  24,  24,  25,  25,  25,  26,  26,  27,  27,  28,  28,  29,  29,  30,
      30,  31,  32,  32,  33,  33,  34,  35,  35,  36,  36,  37,  38,  38,  39,
      40,  40,  41,  42,  43,  43,  44,  45,  46,  47,  48,  48,  49,  50,  51,
      52,  53,  54,  55,  56,  57,  58,  59,  60,  61,  62,  63,  64,  65,  66,
      68,  69,  70,  71,  73,  74,  75,  76,  78,  79,  81,  82,  83,  85,  86,
      88,  90,  91,  93,  94,  96,  98,  99,  101, 103, 105, 107, 109, 110, 112,
      114, 116, 118, 121, 123, 125, 127, 129, 132, 134, 136, 139, 141, 144, 146,
      149, 151, 154, 157, 159, 162, 165, 168, 171, 174, 177, 180, 183, 186, 190,
      193, 196, 200, 203, 207, 211, 214, 218, 222, 226, 230, 234, 238, 242, 248,
      255};

  /*!
   *  Use HSV - hue, saturation, value - to set RGB values
   *
   *  The dim_curve is used only on value and on saturation
   *  (inverted). This looks the most natural.
   *
   * \param[in] hue 0-360
   * \param[in] saturation 0-255
   * \param[in] value O-255
   */
  void FromHSV(int hue, int sat, int value) {
    value = dim_curve[value];
    sat = 255 - dim_curve[255 - sat];

    int base;

    if (sat == 0) {  // Acromatic color (gray). Hue doesn't mind.
      red = value;
      green = value;
      blue = value;
    } else {
      base = ((255 - sat) * value) >> 8;

      switch (hue / 60) {
        case 0:
          red = value;
          green = (((value - base) * hue) / 60) + base;
          blue = base;
          break;

        case 1:
          red = (((value - base) * (60 - (hue % 60))) / 60) + base;
          green = value;
          blue = base;
          break;

        case 2:
          red = base;
          green = value;
          blue = (((value - base) * (hue % 60)) / 60) + base;
          break;

        case 3:
          red = base;
          green = (((value - base) * (60 - (hue % 60))) / 60) + base;
          blue = value;
          break;

        case 4:
          red = (((value - base) * (hue % 60)) / 60) + base;
          green = base;
          blue = value;
          break;

        case 5:
          red = value;
          green = base;
          blue = (((value - base) * (60 - (hue % 60))) / 60) + base;
          break;
      }
    }
  }
};
