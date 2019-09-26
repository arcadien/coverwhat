#include <unity.h>
#include <api/Action.h>

void Expect_Action_to_use_provided_coolDown()
{
  const uint8_t expectedCoolDown = 30;
  uint8_t actualCoolDown;

  Action damage5(0x1, 5, 30);
  actualCoolDown = damage5.GetCoolDownMs();
  TEST_ASSERT_EQUAL_INT(expectedCoolDown, actualCoolDown);
}

void Expect_Action_to_use_provided_value()
{
  const uint8_t expectedValue = 5;
  uint8_t actualValue;

  Action damage5(0x1, 5, 30);
  actualValue = damage5.GetValue();
  TEST_ASSERT_EQUAL_INT(expectedValue, actualValue);
}

void Expect_Action_to_use_provided_entityTag()
{
  const uint8_t expectedEntityTag = 0x1;
  uint8_t actualEntityTag;

  Action damage5(0x1, 5, 30);
  actualEntityTag = damage5.GetTargetEntityTag();
  TEST_ASSERT_EQUAL_INT(expectedEntityTag, actualEntityTag);
}

int main(int, char **)
{
    UNITY_BEGIN();
    RUN_TEST(Expect_Action_to_use_provided_entityTag);
    RUN_TEST(Expect_Action_to_use_provided_value);
    RUN_TEST(Expect_Action_to_use_provided_coolDown);
    return UNITY_END();
}
void tearDown(){}
void setUp(){}
