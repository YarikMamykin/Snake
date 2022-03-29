#include "gtest/gtest.h"
#include "geometry/Point.hpp"
#include <utility>

namespace geometry_test {

TEST(Point, rotate_counter_clockwize)
{
  auto&& p = geometry::Point{100,200};
  auto&& rotation_point = geometry::Point{40,50};
  auto p_to_rotate_counter_clockwize = p;
  p_to_rotate_counter_clockwize.rotate(game_objects::RotationDirection::Counterclockwize, rotation_point);
  EXPECT_EQ(p_to_rotate_counter_clockwize.x, 190);
  EXPECT_EQ(p_to_rotate_counter_clockwize.y, -10);

}

TEST(Point, rotate_clockwize) {
  auto&& p = geometry::Point{100,200};
  auto&& rotation_point = geometry::Point{40,50};
  auto p_to_rotate_clockwize = p;
  p_to_rotate_clockwize.rotate(game_objects::RotationDirection::Clockwize, rotation_point);
  EXPECT_EQ(p_to_rotate_clockwize.x, -110);
  EXPECT_EQ(p_to_rotate_clockwize.y, 110);
}

TEST(Point, lesser) {
  auto&& p1 = geometry::Point{10,10};
  auto&& p2 = geometry::Point{10,20};
  auto&& p3 = geometry::Point{20,10};
  auto&& p4 = geometry::Point{20,20};

  EXPECT_TRUE(p1<p2);
  EXPECT_TRUE(p1<p3);
  EXPECT_TRUE(p1<p4);
}

TEST(Point, greater) {
  auto&& p1 = geometry::Point{10,10};
  auto&& p2 = geometry::Point{10,20};
  auto&& p3 = geometry::Point{20,10};
  auto&& p4 = geometry::Point{20,20};

  EXPECT_TRUE(p2 > p1);
  EXPECT_TRUE(p3 > p1);
  EXPECT_TRUE(p4 > p1);
}

TEST(Point, to_string) {
  geometry::Point p {10,20};
  EXPECT_EQ(p.to_string(), std::string("Point(10:20)\n"));
}

}
