#include <unity.h>

#include <hardware/simulator/Simulator.h>
#include <iostream>
#define PRINT(c) std::cout << c;

#include <chrono>
#include <iostream>

using HardwareType = hardware::Simulator;

void setUp(void) {}

void tearDown(void) {}

void Expect_hardware_to_be_clocked();
void Expect_hardware_to_have_a_primary_action();
void Expect_hardware_to_have_a_secondary_action();
void Expect_hardware_to_be_able_to_sleep_for_some_ms();

int main(int, char **) {
  UNITY_BEGIN();
  RUN_TEST(Expect_hardware_to_be_able_to_sleep_for_some_ms);
  RUN_TEST(Expect_hardware_to_be_clocked);
  RUN_TEST(Expect_hardware_to_have_a_primary_action);
  RUN_TEST(Expect_hardware_to_have_a_secondary_action);
  return UNITY_END();
}

void Expect_hardware_to_be_clocked() {
  // extended Simulator class which
  // count the ticks
  class TestHw : public HardwareType {
   public:
    int tickCount = 0;
    void OnTick() { tickCount++; }
  };
  TestHw hw;

  hw.Setup();
  hw.sleepMs(250);
  hw.Stop();

  TEST_ASSERT(hw.tickCount > 25);
}

void Expect_hardware_to_have_a_primary_action() {
  HardwareType hw;
  hw.TriggerPrimaryAction();
  TEST_ASSERT_EQUAL(1, hw.PrimaryActionCount());
}

void Expect_hardware_to_have_a_secondary_action() {
  HardwareType hw;
  hw.TriggerSecondaryAction();
  TEST_ASSERT_EQUAL(1, hw.SecondaryActionCount());
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
  hw.Stop();

  // sometimes rounding leads to 251ms so
  // add a little tolerance here
  TEST_ASSERT_INT_WITHIN(1, 250, elapsed_ms);
}
