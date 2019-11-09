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

#include <transports/InfraredRc5.h>

#include <cstring>
#include <sstream>

#if not defined(AVR)
#define UNITY_OUTPUT_COLOR
#endif
#include <unity.h>

void Expect_Transport_To_Emit();
void Expect_Transport_To_Receive();

int main(int, char **) {
  UNITY_BEGIN();
  RUN_TEST(Expect_Transport_To_Emit);
  RUN_TEST(Expect_Transport_To_Receive);
  return UNITY_END();
}
void tearDown() {}
void setUp() {}

void Expect_Transport_To_Emit() { transport::InfraredRc5 transport; }
void Expect_Transport_To_Receive() { transport::InfraredRc5 transport; }

