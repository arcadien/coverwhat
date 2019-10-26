#include <tools/RGBColor.h>
#include <unity.h>

void Expect_hsv_value_to_zero_always_produce_black();
void Expect_hsv_hue_0_to_be_red();
void Expect_hsv_hue_60_to_be_yellow();
void Expect_hsv_hue_120_to_be_green();
void Expect_hsv_hue_180_to_be_cyan();
void Expect_hsv_hue_240_to_be_blue();
void Expect_hsv_hue_300_to_be_violet();

int main(int, char **) {
  UNITY_BEGIN();
  RUN_TEST(Expect_hsv_value_to_zero_always_produce_black);
  RUN_TEST(Expect_hsv_hue_0_to_be_red);
  RUN_TEST(Expect_hsv_hue_60_to_be_yellow);
  RUN_TEST(Expect_hsv_hue_120_to_be_green);
  RUN_TEST(Expect_hsv_hue_180_to_be_cyan);
  RUN_TEST(Expect_hsv_hue_240_to_be_blue);
  RUN_TEST(Expect_hsv_hue_300_to_be_violet);
  return UNITY_END();
}
void tearDown() {}
void setUp() {}

void Expect_hsv_hue_0_to_be_red() {
  RGBColor color;
  color.FromHSV(0, 255, 255);
  TEST_ASSERT_EQUAL_INT(255, color.red);
  TEST_ASSERT_EQUAL_INT(0, color.green);
  TEST_ASSERT_EQUAL_INT(0, color.blue);
}

void Expect_hsv_hue_60_to_be_yellow() {
  RGBColor color;
  color.FromHSV(60, 255, 255);
  TEST_ASSERT_EQUAL_INT(255, color.red);
  TEST_ASSERT_EQUAL_INT(255, color.green);
  TEST_ASSERT_EQUAL_INT(0, color.blue);
}

void Expect_hsv_hue_120_to_be_green() {
  RGBColor color;
  color.FromHSV(120, 255, 255);
  TEST_ASSERT_EQUAL_INT(0, color.red);
  TEST_ASSERT_EQUAL_INT(255, color.green);
  TEST_ASSERT_EQUAL_INT(0, color.blue);
}
void Expect_hsv_hue_180_to_be_cyan() {
  RGBColor color;
  color.FromHSV(180, 255, 255);
  TEST_ASSERT_EQUAL_INT(0, color.red);
  TEST_ASSERT_EQUAL_INT(255, color.green);
  TEST_ASSERT_EQUAL_INT(255, color.blue);
}

void Expect_hsv_hue_240_to_be_blue() {
  RGBColor color;
  color.FromHSV(240, 255, 255);
  TEST_ASSERT_EQUAL_INT(0, color.red);
  TEST_ASSERT_EQUAL_INT(0, color.green);
  TEST_ASSERT_EQUAL_INT(255, color.blue);
}

void Expect_hsv_hue_300_to_be_violet() {
  RGBColor color;
  color.FromHSV(300, 255, 255);
  TEST_ASSERT_EQUAL_INT(255, color.red);
  TEST_ASSERT_EQUAL_INT(0, color.green);
  TEST_ASSERT_EQUAL_INT(255, color.blue);
}

void Expect_hsv_value_to_zero_always_produce_black() {
  RGBColor color;
  for (int hue = 0; hue < 256; ++hue) {
    for (int saturation = 0; saturation < 256; ++saturation) {
      color.FromHSV(hue, 0, 0);
      TEST_ASSERT_EQUAL_INT(0, color.red);
      TEST_ASSERT_EQUAL_INT(0, color.green);
      TEST_ASSERT_EQUAL_INT(0, color.blue);
    }
  }
}
