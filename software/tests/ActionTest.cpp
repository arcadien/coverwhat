#include <api/Action.h>
#include <api/Entity.h>
#include <api/Meta.h>
#include <unity.h>

void Expect_Action_to_use_provided_coolDown();
void Expect_Action_to_use_provided_entityTag();
void Expect_Action_to_use_provided_value();
void Expect_default_Action_to_be_creatable();

int main(int, char **) {
  UNITY_BEGIN();
  RUN_TEST(Expect_Action_to_use_provided_entityTag);
  RUN_TEST(Expect_Action_to_use_provided_value);
  RUN_TEST(Expect_Action_to_use_provided_coolDown);
  RUN_TEST(Expect_default_Action_to_be_creatable);
  return UNITY_END();
}
void tearDown() {}
void setUp() {}

void Expect_default_Action_to_be_creatable() { Action action; }

void Expect_Action_to_use_provided_coolDown() {
  const uint8_t expectedCoolDown = 30;
  uint8_t actualCoolDown;
  Action action(Action::Type::DAMAGE, Entity::Tag::Health,
                Action::Amount::AMOUNT_5, 30);
  actualCoolDown = action.GetCoolDownMs();
  TEST_ASSERT_EQUAL_INT(expectedCoolDown, actualCoolDown);
}

void Expect_Action_to_use_provided_value() {
  Action::Amount expectedValue = Action::Amount::AMOUNT_5;
  Action::Amount actualValue;
  Action action(Action::Type::DAMAGE, Entity::Tag::Health,
                Action::Amount::AMOUNT_5, 30);
  actualValue = action.GetAmount();
  TEST_ASSERT_EQUAL_INT(expectedValue, actualValue);
}

void Expect_Action_to_use_provided_entityTag() {
  Entity::Tag expectedEntityTag = Entity::Tag::Health;
  Entity::Tag actualEntityTag;
  Action action(Action::Type::DAMAGE, Entity::Tag::Health,
                Action::Amount::AMOUNT_5, 30);
  actualEntityTag = action.GetTargetEntityTag();
  TEST_ASSERT_EQUAL_INT(expectedEntityTag, actualEntityTag);
}
