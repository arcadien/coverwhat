#include <unity.h>

#include <hardware/simulator/Simulator.h>

#include <chrono>
#include <iostream>
#include <numeric>

void setUp(void) {}

void tearDown(void) {}

void Expect_simulator_to_be_clocked();
void Expect_simulator_to_have_a_primary_action();
void Expect_simulator_to_have_a_secondary_action();
void Expect_simulator_to_be_able_to_sleep_for_some_ms();
void Expect_simulator_to_wait_10ms_during_waitForEvent();
void Expect_simulator_millis_to_overflow_after_max_unsigned_long();
void Expect_simulator_millis_to_not_overflow_in_normal_condition();

int main(int, char **) {
  UNITY_BEGIN();
  RUN_TEST(Expect_simulator_to_be_able_to_sleep_for_some_ms);
  RUN_TEST(Expect_simulator_to_be_clocked);
  RUN_TEST(Expect_simulator_to_have_a_primary_action);
  RUN_TEST(Expect_simulator_to_have_a_secondary_action);
  RUN_TEST(Expect_simulator_to_wait_10ms_during_waitForEvent);
  RUN_TEST(Expect_simulator_millis_to_overflow_after_max_unsigned_long);
  RUN_TEST(Expect_simulator_millis_to_not_overflow_in_normal_condition);
  return UNITY_END();
}

void Expect_simulator_millis_to_not_overflow_in_normal_condition() {
  hardware::Simulator hw;
  hw.sleepMs(100);
  unsigned long iMustBeAround100 = hw.Millis();
  TEST_ASSERT_INT_WITHIN(10, 100, iMustBeAround100);
}
void Expect_simulator_millis_to_overflow_after_max_unsigned_long() {
  unsigned long nearOverflow = std::numeric_limits<unsigned long>::max();
  hardware::Simulator hw(nearOverflow);
  hw.sleepMs(10);
  unsigned long iMustBeASmallValue = hw.Millis();
  TEST_ASSERT_INT_WITHIN(2, 10, iMustBeASmallValue);
}

void Expect_simulator_to_be_clocked() {
  // extended Simulator class which
  // count the ticks
  class TestHw : public hardware::Simulator {
   public:
    int tickCount = 0;
    void OnTick() override { tickCount++; }
  };
  unsigned long tickCount;

  TestHw hw;
  uint16_t sleepDuration = 25 * hardware::Simulator::TICK_INTERVAL_MS;
  hw.sleepMs(sleepDuration);
  tickCount = hw.tickCount;
  hw.Stop();
  TEST_ASSERT_INT_WITHIN(2, 25, tickCount);
}

void Expect_simulator_to_wait_10ms_during_waitForEvent() {
  hardware::Simulator hw;
  auto start = std::chrono::high_resolution_clock::now();
  hw.WaitForEvent();
  auto finish = std::chrono::high_resolution_clock::now();
  std::chrono::duration<double, std::milli> elapsed = finish - start;

  auto const expectedDelay = 2 * hardware::Simulator::TICK_INTERVAL_MS;
  TEST_ASSERT_INT_WITHIN(1, expectedDelay, elapsed.count());
}

void Expect_simulator_to_have_a_primary_action() {
  hardware::Simulator hw;
  hw.TriggerPrimaryAction();
  TEST_ASSERT_EQUAL(1, hw.PrimaryActionCount());
}

void Expect_simulator_to_have_a_secondary_action() {
  hardware::Simulator hw;
  hw.TriggerSecondaryAction();
  TEST_ASSERT_EQUAL(1, hw.SecondaryActionCount());
}

void Expect_simulator_to_be_able_to_sleep_for_some_ms() {
  unsigned long elapsed_ms;
  unsigned long begin;
  unsigned long end;
  hardware::Simulator hw;
  auto start = std::chrono::high_resolution_clock::now();
  hw.sleepMs(250);
  auto finish = std::chrono::high_resolution_clock::now();
  std::chrono::duration<double, std::milli> elapsed = finish - start;

  TEST_ASSERT_INT_WITHIN(1, 250, elapsed.count());
}