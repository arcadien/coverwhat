
#include <api/Action.h>
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
  std::istringstream s;
  s.str("D10\n");
  ui::ConsoleUi ui(s);

  // give some time to the reading thread
  // to parse the input
  std::this_thread::sleep_for(
      std::chrono::milliseconds(ui::ConsoleUi::READ_DELAY_MS * 2));
  TEST_ASSERT(ui.ActionAvailable());

  Action action = ui.GetAction();
  TEST_ASSERT_EQUAL_INT(0, action.Process(10));
}

