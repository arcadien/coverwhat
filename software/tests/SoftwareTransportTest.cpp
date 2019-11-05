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
#include <api/Meta.h>
#include <transports/Software.h>
#include <weapons/Vampire.h>

#ifndef AVR
#define UNITY_OUTPUT_COLOR
#endif
#include <unity.h>

void Expect_action_to_be_sent_to_right_target();

int main(int, char **) {
  UNITY_BEGIN();
  RUN_TEST(Expect_action_to_be_sent_to_right_target);
  return UNITY_END();
}

void tearDown() {}
void setUp() {}

void Expect_action_to_be_sent_to_right_target() {
  // Objective is:
  // a weapon hits player using primary
  // a weapon hits player using secondary
  actors::Player targetPlayer(20);
  transport::Software transport;
  Weapons::Vampire weapon(transport);

  // NOTE: Wire() is a special feature of the
  // software transport
  transport.Wire(&weapon, &targetPlayer);

  weapon.TriggerPrimaryAction();
  weapon.TriggerPrimaryAction();
  weapon.TriggerPrimaryAction();

  // Assert player health
  uint16_t actualHealth = targetPlayer.GetHealth().GetValue();
  TEST_ASSERT_EQUAL_INT(5, actualHealth);

  weapon.TriggerSecondaryAction();
  weapon.TriggerSecondaryAction();
  weapon.TriggerSecondaryAction();

  // Assert player health
  actualHealth = targetPlayer.GetHealth().GetValue();
  TEST_ASSERT_EQUAL_INT(20, actualHealth);
  // Assert player health
}
