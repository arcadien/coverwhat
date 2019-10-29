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

#include <ui/ConsoleUi.h>
#include <sstream>

#if not defined(AVR)
#define UNITY_OUTPUT_COLOR
#endif
#include <unity.h>

void Expect_ui_to_read_input();

int main(int, char **) {
  UNITY_BEGIN();
  RUN_TEST(Expect_ui_to_read_input);
  return UNITY_END();
}
void tearDown() {}
void setUp() {}

void Expect_ui_to_read_input() {
  int actualResult = -1;
  {
    std::istringstream s;
    s.str("D10\n");
    ui::ConsoleUi ui(s);

    // give some time to the reading thread to effectively start
    std::this_thread::sleep_for(
        std::chrono::milliseconds(ui::ConsoleUi::READ_DELAY_MS * 2));
    TEST_ASSERT(ui.ActionAvailable());

    Action action = ui.GetAction();
    actualResult = action.Process(10);
  }

  // ensure ConsoleUi thread finishes
  std::this_thread::sleep_for(
      std::chrono::milliseconds(ui::ConsoleUi::READ_DELAY_MS));

  TEST_ASSERT_EQUAL_INT(0, actualResult);
}

