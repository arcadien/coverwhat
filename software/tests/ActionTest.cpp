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
#include <api/Entity.h>
#include <api/Meta.h>

#if not defined(AVR)
#define UNITY_OUTPUT_COLOR
#endif
#include <unity.h>

void Expect_Action_to_use_provided_coolDown();
void Expect_Action_to_use_provided_entityTag();
void Expect_Action_to_use_provided_value();
void Expect_default_Action_to_be_creatable();

void Expect_Damage_type_to_decrease_value();
void Expect_Heal_type_to_increase_value();
void Expect_None_type_to_keep_value_untouched();
void Expect_Resurect_to_do_nothing_on_non_dead_player();
void Expect_Entity_value_cannot_be_lower_than_zero();
void Expect_Damage_to_lower_down_to_zero_not_less();

int main(int, char **) {
  UNITY_BEGIN();
  RUN_TEST(Expect_Action_to_use_provided_entityTag);
  RUN_TEST(Expect_Action_to_use_provided_value);
  RUN_TEST(Expect_Action_to_use_provided_coolDown);
  RUN_TEST(Expect_default_Action_to_be_creatable);
  RUN_TEST(Expect_Damage_type_to_decrease_value);
  RUN_TEST(Expect_Heal_type_to_increase_value);
  RUN_TEST(Expect_None_type_to_keep_value_untouched);
  RUN_TEST(Expect_Resurect_to_do_nothing_on_non_dead_player);
  RUN_TEST(Expect_Entity_value_cannot_be_lower_than_zero);
  RUN_TEST(Expect_Damage_to_lower_down_to_zero_not_less);
  return UNITY_END();
}
void tearDown() {}
void setUp() {}

void Expect_Damage_to_lower_down_to_zero_not_less() {
  Action action(Action::Type::DAMAGE, Entity::Tag::Health,
                Action::Amount::AMOUNT_50, 30);

  auto result = action.Process(30);

  TEST_ASSERT_EQUAL_INT(0, result);
}

void Expect_Entity_value_cannot_be_lower_than_zero() {
  Action action(Action::Type::DAMAGE, Entity::Tag::Health,
                Action::Amount::AMOUNT_5, 30);

  auto result = action.Process(0);

  TEST_ASSERT_EQUAL_INT(0, result);
}

void Expect_Damage_type_to_decrease_value() {
  Action action(Action::Type::DAMAGE, Entity::Tag::Health,
                Action::Amount::AMOUNT_5, 30);

  auto result = action.Process(30);

  TEST_ASSERT_EQUAL_INT(25, result);
}

void Expect_Heal_type_to_increase_value() {
  Action action(Action::Type::HEAL, Entity::Tag::Health,
                Action::Amount::AMOUNT_5, 30);

  auto result = action.Process(0);

  TEST_ASSERT_EQUAL_INT(5, result);
}

void Expect_None_type_to_keep_value_untouched() {
  Action action(Action::Type::NONE, Entity::Tag::Health,
                Action::Amount::AMOUNT_5, 30);

  auto result = action.Process(30);

  TEST_ASSERT_EQUAL_INT(30, result);
}

void Expect_Resurect_to_do_nothing_on_non_dead_player() {}

void Expect_Action_to_use_provided_coolDown() {
  const uint8_t expectedCoolDown = 30;
  uint8_t actualCoolDown;
  Action action(Action::Type::DAMAGE, Entity::Tag::Health,
                Action::Amount::AMOUNT_5, 30);
  actualCoolDown = action.GetCoolDownMs();
  TEST_ASSERT_EQUAL_INT(expectedCoolDown, actualCoolDown);
}

void Expect_Action_to_use_provided_value() {
  Action::Amount expectedValue = Action::Amount::AMOUNT_5;
  Action::Amount actualValue;
  Action action(Action::Type::DAMAGE, Entity::Tag::Health,
                Action::Amount::AMOUNT_5, 30);
  actualValue = action.GetAmount();
  TEST_ASSERT_EQUAL_INT(expectedValue, actualValue);
}

void Expect_Action_to_use_provided_entityTag() {
  Entity::Tag expectedEntityTag = Entity::Tag::Health;
  Entity::Tag actualEntityTag;
  Action action(Action::Type::DAMAGE, Entity::Tag::Health,
                Action::Amount::AMOUNT_5, 30);
  actualEntityTag = action.GetTargetEntityTag();
  TEST_ASSERT_EQUAL_INT(expectedEntityTag, actualEntityTag);
}

void Expect_default_Action_to_be_creatable() { Action action; }
