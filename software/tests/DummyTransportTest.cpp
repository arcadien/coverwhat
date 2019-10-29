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

#include <api/Meta.h>
#include <transports/Dummy.h>

#if not defined(AVR)
#define UNITY_OUTPUT_COLOR
#endif
#include <unity.h>

void Expect_Dummy_Transport_to_respect_interface();
void Expect_Dummy_Transport_to_return_default_action();
void Expect_Dummy_Transport_to_never_have_available_action();

int main(int, char **) {
  UNITY_BEGIN();
  RUN_TEST(Expect_Dummy_Transport_to_respect_interface);
  RUN_TEST(Expect_Dummy_Transport_to_return_default_action);
  RUN_TEST(Expect_Dummy_Transport_to_never_have_available_action);
  return UNITY_END();
}
void tearDown() {}
void setUp() {}

void Expect_Dummy_Transport_to_respect_interface() {
  transport::Dummy dummyTransport;
  auto action = Meta::Actions::HEAL5;
  dummyTransport.Queue(action);
}

void Expect_Dummy_Transport_to_return_default_action() {
  transport::Dummy dummyTransport;
  auto action = dummyTransport.GetAction();
  TEST_ASSERT(action.GetTargetEntityTag() == Entity::Tag::None);
  TEST_ASSERT(action.GetCoolDownMs() == 0);
  TEST_ASSERT(action.GetAmount() == Action::Amount::AMOUNT_0);
}

void Expect_Dummy_Transport_to_never_have_available_action() {
  transport::Dummy dummyTransport;
  TEST_ASSERT(!dummyTransport.ActionAvailable());
}
