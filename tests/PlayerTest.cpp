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

#include <actors/Player.h>

#ifndef AVR
#define UNITY_OUTPUT_COLOR
#endif
#include <unity.h>

void Expect_Player_to_be_set_in_red_team();
void Expect_Player_to_be_set_in_blue_team();
void Expect_default_Player_to_be_set_in_default_team();

int main(int, char **) {
  UNITY_BEGIN();
  RUN_TEST(Expect_Player_to_be_set_in_red_team);
  RUN_TEST(Expect_Player_to_be_set_in_blue_team);
  RUN_TEST(Expect_default_Player_to_be_set_in_default_team);
  return UNITY_END();
}
void tearDown() {}
void setUp() {}

void Expect_Player_to_be_set_in_red_team() {
  actors::Player p(Team::Red);
  TEST_ASSERT_EQUAL(Team::Red, p.GetTeam());
}

void Expect_Player_to_be_set_in_blue_team() {
  actors::Player p(Team::Blue);
  TEST_ASSERT_EQUAL(Team::Blue, p.GetTeam());
}

void Expect_default_Player_to_be_set_in_default_team() {
  actors::Player p;
  TEST_ASSERT_EQUAL(Team::None, p.GetTeam());
}
