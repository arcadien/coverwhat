#include <unity.h>

#include <hardware/avr/Atmega328p.h>

#include <Arduino.h>
#include <stdint.h>

void setUp(void) {}

void tearDown(void) {}

void Expect_atmega328p_to_be_clocked();
// void Expect_atmega328p_to_have_a_primary_action();
// void Expect_atmega328p_to_have_a_secondary_action();
void Expect_atmega328p_to_be_able_to_sleep_for_some_ms();
void Expect_atmega328p_to_wait_10ms_during_waitForEvent();
void Expect_atmega328p_millis_to_not_overflow_in_normal_condition();

int main(int, char **) {
  UNITY_BEGIN();
  RUN_TEST(Expect_atmega328p_to_be_able_to_sleep_for_some_ms);
  RUN_TEST(Expect_atmega328p_to_be_clocked);
  // RUN_TEST(Expect_atmega328p_to_have_a_primary_action);
  // RUN_TEST(Expect_atmega328p_to_have_a_secondary_action);
  RUN_TEST(Expect_atmega328p_to_wait_10ms_during_waitForEvent);
  RUN_TEST(Expect_atmega328p_millis_to_not_overflow_in_normal_condition);
  return UNITY_END();
}

void Expect_atmega328p_millis_to_not_overflow_in_normal_condition() {
  hardware::Atmega328p hw;
  hw.sleepMs(100);
  unsigned long iMustBeAround100 = hw.Millis();
  TEST_ASSERT_INT_WITHIN(10, 100, iMustBeAround100);
}

void Expect_atmega328p_to_be_clocked() {
  // extended Simulator class which
  // count the ticks
  class TestHw : public hardware::Atmega328p {
   public:
    int tickCount = 0;
    void OnTick() override { tickCount++; }
  };
  unsigned long tickCount;

  TestHw hw;
  uint16_t sleepDuration = 25 * hardware::Atmega328p::TICK_INTERVAL_MS;
  hw.sleepMs(sleepDuration);
  tickCount = hw.tickCount;
  hw.Stop();
  TEST_ASSERT_INT_WITHIN(2, 25, tickCount);
}

void Expect_atmega328p_to_wait_10ms_during_waitForEvent() {
  hardware::Atmega328p hw;
  unsigned long start = millis();
  hw.WaitForEvent();
  unsigned long finish = millis();
  unsigned long elapsed = finish - start;

  auto const expectedDelay = 2 * hardware::Atmega328p::TICK_INTERVAL_MS;
  TEST_ASSERT_INT_WITHIN(1, expectedDelay, elapsed);
}

// void Expect_atmega328p_to_have_a_primary_action() {
//   hardware::Atmega328p hw;
//   hw.TriggerPrimaryAction();
//   TEST_ASSERT_EQUAL(1, hw.PrimaryActionCount());
// }

// void Expect_atmega328p_to_have_a_secondary_action() {
//   hardware::Atmega328p hw;
//   hw.TriggerSecondaryAction();
//   TEST_ASSERT_EQUAL(1, hw.SecondaryActionCount());
// }

void Expect_atmega328p_to_be_able_to_sleep_for_some_ms() {
  hardware::Atmega328p hw;
  unsigned long start = millis();
  hw.sleepMs(250);
  unsigned long finish = millis();
  unsigned long elapsed = finish - start;

  TEST_ASSERT_INT_WITHIN(1, 250, elapsed);
}
