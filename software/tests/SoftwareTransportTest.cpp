#include <actors/Player.h>
#include <api/Meta.h>
#include <transports/Software.h>
#include <weapons/Vampire.h>

#include <unity.h>

void Expect_action_to_be_sent_to_right_target();

int main(int, char **) {
  UNITY_BEGIN();
  RUN_TEST(Expect_action_to_be_sent_to_right_target);
  return UNITY_END();
}

void tearDown() {
}
void setUp() {
}

void Expect_action_to_be_sent_to_right_target() {
  // Objective is:
  // a weapon hits player using primary
  // a weapon hits player using secondary
  actors::Player targetPlayer;
  targetPlayer.SetEntityValue(Entity::Tag::Health, 20);
  transport::Software transport;
  Weapons::Vampire weapon(transport);

  // NOTE: Wire() is a special feature of the
  // software transport
  transport.Wire(&weapon, &targetPlayer);

  weapon.TriggerPrimaryAction();
  weapon.TriggerPrimaryAction();
  weapon.TriggerPrimaryAction();

  // Assert player health
  uint16_t actualHealth = targetPlayer.GetEntityValue(Entity::Tag::Health);
  TEST_ASSERT_EQUAL_INT(5, actualHealth);

  weapon.TriggerSecondaryAction();
  weapon.TriggerSecondaryAction();
  weapon.TriggerSecondaryAction();

  // Assert player health
  actualHealth = targetPlayer.GetEntityValue(Entity::Tag::Health);
  TEST_ASSERT_EQUAL_INT(20, actualHealth);
  // Assert player health
}
