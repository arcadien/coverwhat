#include <actions/StringActionFactory.h>
#include <api/Action.h>
#include <api/Entity.h>

#if not defined(AVR)
#define UNITY_OUTPUT_COLOR
#endif
#include <unity.h>

void Expect_factory_able_to_create_H0();
void Expect_factory_able_to_create_H1();
void Expect_factory_able_to_create_H5();
void Expect_factory_able_to_create_H10();
void Expect_factory_able_to_create_H25();
void Expect_factory_able_to_create_H50();
void Expect_factory_able_to_create_H100();
void Expect_factory_able_to_create_H250();
void Expect_factory_to_do_nothing_on_unknown_amount();

void Expect_factory_able_to_create_D0();
void Expect_factory_able_to_create_D1();
void Expect_factory_able_to_create_D5();
void Expect_factory_able_to_create_D10();
void Expect_factory_able_to_create_D25();
void Expect_factory_able_to_create_D50();
void Expect_factory_able_to_create_D100();
void Expect_factory_able_to_create_D250();

int main(int, char **) {
  UNITY_BEGIN();
  RUN_TEST(Expect_factory_able_to_create_H0);
  RUN_TEST(Expect_factory_able_to_create_H1);
  RUN_TEST(Expect_factory_able_to_create_H5);
  RUN_TEST(Expect_factory_able_to_create_H10);
  RUN_TEST(Expect_factory_able_to_create_H25);
  RUN_TEST(Expect_factory_able_to_create_H50);
  RUN_TEST(Expect_factory_able_to_create_H100);
  RUN_TEST(Expect_factory_able_to_create_H250);
  RUN_TEST(Expect_factory_to_do_nothing_on_unknown_amount);

  RUN_TEST(Expect_factory_able_to_create_D0);
  RUN_TEST(Expect_factory_able_to_create_D1);
  RUN_TEST(Expect_factory_able_to_create_D5);
  RUN_TEST(Expect_factory_able_to_create_D10);
  RUN_TEST(Expect_factory_able_to_create_D25);
  RUN_TEST(Expect_factory_able_to_create_D50);
  RUN_TEST(Expect_factory_able_to_create_D100);
  RUN_TEST(Expect_factory_able_to_create_D250);

  return UNITY_END();
}
void tearDown() {}
void setUp() {}

static const int TEN = 10;
static const int HUNDRED = 100;

void Expect_factory_able_to_create_H0() {
  Action action = actions::StringActionFactory<Action>::Create("H0");
  TEST_ASSERT_EQUAL_INT(TEN, action.Process(TEN));
}
void Expect_factory_able_to_create_H1() {
  Action action = actions::StringActionFactory<Action>::Create("H1");
  TEST_ASSERT_EQUAL_INT(11, action.Process(TEN));
}
void Expect_factory_able_to_create_H5() {
  Action action = actions::StringActionFactory<Action>::Create("H5");
  TEST_ASSERT_EQUAL_INT(15, action.Process(TEN));
}
void Expect_factory_able_to_create_H10() {
  Action action = actions::StringActionFactory<Action>::Create("H10");
  TEST_ASSERT_EQUAL_INT(20, action.Process(TEN));
}
void Expect_factory_able_to_create_H25() {
  Action action = actions::StringActionFactory<Action>::Create("H25");
  TEST_ASSERT_EQUAL_INT(125, action.Process(HUNDRED));
}
void Expect_factory_able_to_create_H50() {
  Action action = actions::StringActionFactory<Action>::Create("H50");
  TEST_ASSERT_EQUAL_INT(150, action.Process(HUNDRED));
}
void Expect_factory_able_to_create_H100() {
  Action action = actions::StringActionFactory<Action>::Create("H100");
  TEST_ASSERT_EQUAL_INT(300, action.Process(200));
}
void Expect_factory_able_to_create_H250() {
  Action action = actions::StringActionFactory<Action>::Create("H250");
  TEST_ASSERT_EQUAL_INT(750, action.Process(500));
}
void Expect_factory_to_do_nothing_on_unknown_amount() {
  Action action = actions::StringActionFactory<Action>::Create("HBEE");
  TEST_ASSERT_EQUAL_INT(TEN, action.Process(TEN));
}

void Expect_factory_able_to_create_D0() {
  Action action = actions::StringActionFactory<Action>::Create("D0");
  TEST_ASSERT_EQUAL_INT(TEN, action.Process(TEN));
}
void Expect_factory_able_to_create_D1() {
  Action action = actions::StringActionFactory<Action>::Create("D1");
  TEST_ASSERT_EQUAL_INT(9, action.Process(TEN));
}
void Expect_factory_able_to_create_D5() {
  Action action = actions::StringActionFactory<Action>::Create("D5");
  TEST_ASSERT_EQUAL_INT(5, action.Process(TEN));
}
void Expect_factory_able_to_create_D10() {
  Action action = actions::StringActionFactory<Action>::Create("D10");
  TEST_ASSERT_EQUAL_INT(0, action.Process(TEN));
}
void Expect_factory_able_to_create_D25() {
  Action action = actions::StringActionFactory<Action>::Create("D25");
  TEST_ASSERT_EQUAL_INT(75, action.Process(HUNDRED));
}
void Expect_factory_able_to_create_D50() {
  Action action = actions::StringActionFactory<Action>::Create("D50");
  TEST_ASSERT_EQUAL_INT(50, action.Process(HUNDRED));
}
void Expect_factory_able_to_create_D100() {
  Action action = actions::StringActionFactory<Action>::Create("D100");
  TEST_ASSERT_EQUAL_INT(HUNDRED, action.Process(200));
}
void Expect_factory_able_to_create_D250() {
  Action action = actions::StringActionFactory<Action>::Create("D250");
  TEST_ASSERT_EQUAL_INT(250, action.Process(500));
}
