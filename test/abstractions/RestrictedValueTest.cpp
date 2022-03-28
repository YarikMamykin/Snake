#include "gtest/gtest.h"
#include <string>
#include "abstractions/values/RestrictedValue.hpp"

namespace abstractions_testing {
  
  using namespace abstractions::values;

  TEST(RestrictedValueTest, SetValueInBounds) {
    auto restricted_value = RestrictedValue(1u, 1u, 10u);
    EXPECT_EQ(1u, restricted_value.get_restricted_value());
    restricted_value.set_value(5u);
    EXPECT_EQ(5u, restricted_value.get_restricted_value());
    restricted_value.set_value(6u);
    EXPECT_EQ(6u, restricted_value.get_restricted_value());
    restricted_value.set_value(1u);
    EXPECT_EQ(1u, restricted_value.get_restricted_value());
    restricted_value.set_value(10u);
    EXPECT_EQ(10u, restricted_value.get_restricted_value());
  }

  TEST(RestrictedValueTest, SetValueOutOfBounds) {
    auto restricted_value = RestrictedValue(1u, 1u, 10u);
    ASSERT_EQ(1u, restricted_value.get_restricted_value());
    restricted_value.set_value(11u);
    EXPECT_EQ(10u, restricted_value.get_restricted_value());
    restricted_value.set_value(0u);
    EXPECT_EQ(1u, restricted_value.get_restricted_value());
  }
}
