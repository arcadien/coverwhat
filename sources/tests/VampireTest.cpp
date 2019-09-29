#include <unity.h>

#include <api/Action.h>
#include <api/Meta.h>
#include <api/Actor.h>

#include <weapons/Vampire.h>

void Expect_Vampire_to_damage_target_user_when_using_vampire_primary_action();
void Expect_Vampire_to_heal_target_user_when_using_vampire_secondary_action();

int main(int, char **)
{
    UNITY_BEGIN();
    RUN_TEST(Expect_Vampire_to_damage_target_user_when_using_vampire_primary_action);
    RUN_TEST(Expect_Vampire_to_heal_target_user_when_using_vampire_secondary_action);
    return UNITY_END();
}
void tearDown(){}
void setUp(){}


void Expect_Vampire_to_damage_target_user_when_using_vampire_primary_action()
{
  /*
  Actor::Weapon vampire = Weapons::VAMPIRE;
  Actor::Player target;
  auto action = vampire.GetPrimary(); 
  Meta::Entities::Health initialHealth(10);
  target.SetEntityValue(Meta::Entities::Health, initialhealth);
  target.accept(action);
  Meta::Entities::Health expectedHealth(5);
  auto actualHealth = target.GetEntityValue(Meta::Entities::Health);
  TEST_ASSERT_EQUAL_INT(actualHealth, expectedHealth);
  */
}

void Expect_Vampire_to_heal_target_user_when_using_vampire_secondary_action()
{
  /*
  Actor::Weapon vampire = Weapons::VAMPIRE;
  Actor::Player target;
  auto action = vampire.GetSecondary(); 
  Meta::Entities::Health initialHealth(10);
  target.SetEntityValue(Meta::Entities::Health, initialhealth);
  target.accept(action);
  Meta::Entities::Health expectedHealth(15);
  auto actualHealth = target.GetEntityValue(Meta::Entities::Health);
  TEST_ASSERT_EQUAL_INT(actualHealth, expectedHealth);
  */
}
