#include <unity.h>
#include <api/Action.h>
#include <api/Meta.h>

void Expect_Weapon_to_return_right_primary_action();
void Expect_Weapon_to_return_right_secondary_action();

int main(int, char **)
{
    UNITY_BEGIN();
    RUN_TEST(Expect_Weapon_to_return_right_primary_action);
    RUN_TEST(Expect_Weapon_to_return_right_secondary_action);
    return UNITY_END();
}
void tearDown(){}
void setUp(){}

class TestWeapon : public Actor::Weapon
{
  public:
  TestWeapon() : Actor::Weapon(Meta::Actions::DAMAGE5, Meta::Actions::HEAL5){}
};

TestWeapon WEAPON_UNDER_TEST;

void Expect_Weapon_to_return_right_primary_action(){
  Action const& actualPrimary = WEAPON_UNDER_TEST.GetPrimary();
  TEST_ASSERT(&actualPrimary == &Meta::Actions::DAMAGE5);
}

void Expect_Weapon_to_return_right_secondary_action(){
  Action const& actualSecondary = WEAPON_UNDER_TEST.GetSecondary();
  TEST_ASSERT(&actualSecondary == &Meta::Actions::HEAL5);
}

