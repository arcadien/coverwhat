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

#include <api/Entity.h>

#ifndef AVR
#define UNITY_OUTPUT_COLOR
#endif
#include <unity.h>

void Expect_Entity_value_cannot_exceed_its_initial_value();
void Expect_Entity_value_be_settable_between_zero_and_initial_value();
void Expect_Entity_Tag_None_to_be_useable();

int main(int, char **) {
  UNITY_BEGIN();
  RUN_TEST(Expect_Entity_value_cannot_exceed_its_initial_value);
  RUN_TEST(Expect_Entity_value_be_settable_between_zero_and_initial_value);
  RUN_TEST(Expect_Entity_Tag_None_to_be_useable);
  return UNITY_END();
}
void tearDown() {}
void setUp() {}

void Expect_Entity_Tag_None_to_be_useable() {
  Entity entity(Entity::Tag::None, 0);
}

void Expect_Entity_value_be_settable_between_zero_and_initial_value() {
  Entity entity(Entity::Tag::Health, 50);
  entity.SetValue(10);
  TEST_ASSERT_EQUAL_INT(10, entity.GetValue());
}
void Expect_Entity_value_cannot_exceed_its_initial_value() {
  Entity entity(Entity::Tag::Health, 50);
  entity.SetValue(100);
  TEST_ASSERT_EQUAL_INT(50, entity.GetValue());
}
