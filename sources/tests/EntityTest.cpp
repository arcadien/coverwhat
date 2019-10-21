#include <api/Entity.h>
#include <unity.h>

void Expect_Entity_value_cannot_exceed_its_initial_value();
void Expect_Entity_value_be_settable_between_zero_and_initial_value();
void Expect_Entity_Tag_None_to_be_useable();

int main(int, char **) {
  UNITY_BEGIN();
  RUN_TEST(Expect_Entity_value_cannot_exceed_its_initial_value);
  RUN_TEST(Expect_Entity_value_be_settable_between_zero_and_initial_value);
  RUN_TEST(Expect_Entity_Tag_None_to_be_useable);
  return UNITY_END();
}
void tearDown() {}
void setUp() {}

void Expect_Entity_Tag_None_to_be_useable() {
  Entity entity(Entity::Tag::None, 0);
}

void Expect_Entity_value_be_settable_between_zero_and_initial_value() {
  Entity entity(Entity::Tag::Health, 50);
  entity.SetValue(10);
  TEST_ASSERT_EQUAL_INT(10, entity.GetValue());
}
void Expect_Entity_value_cannot_exceed_its_initial_value() {
  Entity entity(Entity::Tag::Health, 50);
  entity.SetValue(100);
  TEST_ASSERT_EQUAL_INT(50, entity.GetValue());
}
