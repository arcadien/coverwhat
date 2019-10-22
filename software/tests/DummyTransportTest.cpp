#include <api/Meta.h>
#include <transports/Dummy.h>

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
