#include "gtest/gtest.h"
#include "Rectangle.hpp"

namespace {
}

namespace geometry_test {

TEST(Rectangle, Move)
{
  auto rectangle = geometry::Rectangle();
  ASSERT_EQ(0, rectangle.x);
  ASSERT_EQ(0, rectangle.y);
  rectangle.move(100,100);
  EXPECT_EQ(100, rectangle.x);
  EXPECT_EQ(100, rectangle.y);
}

TEST(Rectangle, BelongsTo) 
{
  geometry::Rectangle rectangle = { .x = 100, .y = 100, .width = 100, .height = 100 };
  geometry::Rectangle inside_rectangle = { .x = 150, .y = 120, .width = 10, .height = 10 };
  geometry::Rectangle outside_rectangle = { .x = 0, .y = 0, .width = 1000, .height = 1000 };
  geometry::Rectangle partially_placed_rectangle = { .x = 120, .y = 120, .width = 1000, .height = 1000 };
  EXPECT_TRUE(rectangle.belongs_to(outside_rectangle));
  EXPECT_TRUE(inside_rectangle.belongs_to(rectangle));
  EXPECT_FALSE(rectangle.belongs_to(inside_rectangle));
  EXPECT_FALSE(rectangle.belongs_to(partially_placed_rectangle));
}

TEST(Rectangle, GetVertices) {
  geometry::Rectangle rectangle = { 
    .x = 100, 
    .y = 100, 
    .width = 100, 
    .height = 100 
  };

  const auto&& tl = rectangle.top_left();
  const auto&& tr = rectangle.top_right();
  const auto&& bl = rectangle.bottom_left();
  const auto&& br = rectangle.bottom_right();

  EXPECT_EQ(tl.x, rectangle.x);
  EXPECT_EQ(tl.y, rectangle.y);

  EXPECT_EQ(tr.x, rectangle.x + rectangle.width);
  EXPECT_EQ(tr.y, rectangle.y);

  EXPECT_EQ(bl.x, rectangle.x);
  EXPECT_EQ(bl.y, rectangle.y + rectangle.height);

  EXPECT_EQ(br.x, rectangle.x + rectangle.width);
  EXPECT_EQ(br.y, rectangle.y + rectangle.height);
}

TEST(Rectangle, Rotate)
{
  geometry::Rectangle rectangle = { 
    .x = 100, 
    .y = 100, 
    .width = 100, 
    .height = 100 
  };

  std::vector<geometry::Rectangle> test_rectangles = { rectangle, rectangle, rectangle };

  test_rectangles[0].rotate(game_objects::RotationDirection::Counterclockwize, rectangle.top_left());
  EXPECT_TRUE(test_rectangles[0].top_right() == rectangle.top_left());

  test_rectangles[1].rotate(game_objects::RotationDirection::Clockwize, rectangle.top_left());
  test_rectangles[2].rotate(game_objects::RotationDirection::NONE, rectangle.top_left());
}

}
