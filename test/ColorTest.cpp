#include "gtest/gtest.h"
#include "Color.hpp"

namespace colors_test {

  using Color = color::Color;

TEST(ColorTest, CreateRedFromLong) {
  Color color(255UL << 16);
  EXPECT_EQ(color.red, 255U);
  EXPECT_EQ(color.green, 0U);
  EXPECT_EQ(color.blue, 0U);
}

TEST(ColorTest, CreateGreenFromLong) {
  Color color(255UL << 8);
  EXPECT_EQ(color.red, 0U);
  EXPECT_EQ(color.green, 255U);
  EXPECT_EQ(color.blue, 0U);
}

TEST(ColorTest, CreateBlueFromLong) {
  Color color(255UL);
  EXPECT_EQ(color.red, 0U);
  EXPECT_EQ(color.green, 0U);
  EXPECT_EQ(color.blue, 255U);
}

TEST(ColorTest, CreateBlackFromLong) {
  Color color(0UL);
  EXPECT_EQ(color.red, 0U);
  EXPECT_EQ(color.green, 0U);
  EXPECT_EQ(color.blue, 0U);
}

TEST(ColorTest, CreatePurpleFromLong) {
  Color color((255UL << 16) | 255UL);
  EXPECT_EQ(color.red, 255U);
  EXPECT_EQ(color.green, 0U);
  EXPECT_EQ(color.blue, 255U);
}

TEST(ColorTest, CreateWhiteFromLong) {
  Color color((255UL << 16) | (255UL << 8) | 255UL);
  EXPECT_EQ(color.red, 255U);
  EXPECT_EQ(color.green, 255U);
  EXPECT_EQ(color.blue, 255U);
}

TEST(ColorTest, CreateRedFromHex) {
  Color color("#ff0000");
  EXPECT_EQ(color.red, 255U);
  EXPECT_EQ(color.green, 0U);
  EXPECT_EQ(color.blue, 0U);
}

TEST(ColorTest, CreateGreenFromHex) {
  Color color("#00ff00");
  EXPECT_EQ(color.red, 0U);
  EXPECT_EQ(color.green, 255U);
  EXPECT_EQ(color.blue, 0U);
}

TEST(ColorTest, CreateBlueFromHex) {
  Color color("#0000ff");
  EXPECT_EQ(color.red, 0U);
  EXPECT_EQ(color.green, 0U);
  EXPECT_EQ(color.blue, 255U);
}

TEST(ColorTest, CreateBlackFromHex) {
  Color color("#000000");
  EXPECT_EQ(color.red, 0U);
  EXPECT_EQ(color.green, 0U);
  EXPECT_EQ(color.blue, 0U);
}

TEST(ColorTest, CreatePurpleFromHex) {
  Color color("#ff00ff");
  EXPECT_EQ(color.red, 255U);
  EXPECT_EQ(color.green, 0U);
  EXPECT_EQ(color.blue, 255U);
}

TEST(ColorTest, CreateWhiteFromHex) {
  Color color("#ffffff");
  EXPECT_EQ(color.red, 255U);
  EXPECT_EQ(color.green, 255U);
  EXPECT_EQ(color.blue, 255U);
}

TEST(ColorTest, ConvertGreenToLong) {
  Color color(255UL << 8);
  EXPECT_EQ(color.to_long(), (255UL << 8));
}
}
