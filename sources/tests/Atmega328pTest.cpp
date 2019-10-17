#include <unity.h>

#include <hardware/avr/Atmega328p.h>

using HardwareType = hardware::Atmega328p;

void setUp(void) {
}

void tearDown(void) {
}

void Expect_hardware_to_be_clocked() {
  // extended Simulator class which
  // count the ticks
  class TestHw : public HardwareType {
  public:
    int tickCount = 0;
    void OnTick() {
      tickCount++;
    }
  };
  TestHw hw;
  hw.Setup();
  hw.sleepMs(250);
  hw.Stop();
  TEST_ASSERT(hw.tickCount > 25);
}

void Expect_hardware_to_be_able_to_sleep_for_some_ms() {
  HardwareType hw;
  hw.Setup();

  unsigned long begin;
  unsigned long end;

  begin = hw.Millis();
  hw.sleepMs(250);
  end = hw.Millis();

  int elapsed_ms = end - begin;

  // sometimes rounding leads to 251ms so
  // add a little tolerance here
  TEST_ASSERT_INT_WITHIN(1, 250, elapsed_ms);
}

int main(int, char **) {
  UNITY_BEGIN();
  RUN_TEST(Expect_hardware_to_be_able_to_sleep_for_some_ms);
  RUN_TEST(Expect_hardware_to_be_clocked);
  return UNITY_END();
}
