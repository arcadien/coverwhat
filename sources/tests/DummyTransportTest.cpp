#include <api/Meta.h>
#include <transports/Dummy.h>

#include <unity.h>

void Expect_Dummy_Transport_to_respect_interface();

int main(int, char **) {
  UNITY_BEGIN();
  RUN_TEST(Expect_Dummy_Transport_to_respect_interface);
  return UNITY_END();
}
void tearDown() {
}
void setUp() {
}

void Expect_Dummy_Transport_to_respect_interface() {
  transport::Dummy dummyTransport;
  auto action = Meta::Actions::HEAL5;
  dummyTransport.Queue(action);
}

