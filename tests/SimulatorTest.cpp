#include <unity.h>

//
// The simulated hardware won't be executed on real hardware
//
#if(not defined AVR)

#include <hardware/simulator/Simulator.h>

#include <chrono>
#include <iostream>

void setUp(void)
{
}

void tearDown(void)
{
}

void Expect_hardware_to_be_able_to_sleep_for_some_ms()
{
  hardware::Simulator hw;
  
    std::chrono::time_point<std::chrono::system_clock> start, end;
    start = std::chrono::system_clock::now();
    hw.sleepMs(250);
    end = std::chrono::system_clock::now();
 
    int elapsed_ms = std::chrono::duration_cast<std::chrono::milliseconds>
                             (end-start).count();
 
    TEST_ASSERT(250 == elapsed_ms);
}
   
int main(int, char **)
{
    UNITY_BEGIN();
    RUN_TEST(Expect_hardware_to_be_able_to_sleep_for_some_ms);

    return UNITY_END();
}

#else

int main(int, char **)
{
    UNITY_BEGIN();
    return UNITY_END();
}
#endif
