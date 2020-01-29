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

#include <actors/Weapon.h>
#include <api/Action.h>
#include <api/Meta.h>
#include <transports/Dummy.h>

#ifndef AVR
#define UNITY_OUTPUT_COLOR
#endif
#include <unity.h>

void Expect_Weapon_to_return_right_primary_action();
void Expect_Weapon_to_return_right_secondary_action();

int main(int, char **) {
  UNITY_BEGIN();
  RUN_TEST(Expect_Weapon_to_return_right_primary_action);
  RUN_TEST(Expect_Weapon_to_return_right_secondary_action);
  return UNITY_END();
}
void tearDown() {}
void setUp() {}

class TestWeapon : public actors::Weapon {
public:
  TestWeapon(transport::ITransport &transport)
      : actors::Weapon(transport, Meta::Actions::DAMAGE5,
                       Meta::Actions::HEAL5) {}
};

transport::Dummy dummyTransport;
TestWeapon WEAPON_UNDER_TEST(dummyTransport);

void Expect_Weapon_to_return_right_primary_action() {
  Action const &actualPrimary = WEAPON_UNDER_TEST.GetPrimary();
  TEST_ASSERT(&actualPrimary == &Meta::Actions::DAMAGE5);
}

void Expect_Weapon_to_return_right_secondary_action() {
  Action const &actualSecondary = WEAPON_UNDER_TEST.GetSecondary();
  TEST_ASSERT(&actualSecondary == &Meta::Actions::HEAL5);
}
