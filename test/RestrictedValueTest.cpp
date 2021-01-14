#include "gtest/gtest.h"
#include <string>
#include "RestrictedValue.hpp"

namespace abstractions_testing {
  
  using namespace abstractions;

  TEST(RestrictedValueTest, SetValueInBounds) {
    auto restricted_value = RestrictedValue<unsigned long>(1u, 1u, 10u);
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
    auto restricted_value = RestrictedValue<unsigned long>(1u, 1u, 10u);
    ASSERT_EQ(1u, restricted_value.get_restricted_value());
    restricted_value.set_value(11u);
    EXPECT_EQ(1u, restricted_value.get_restricted_value());
    restricted_value.set_value(0u);
    EXPECT_EQ(1u, restricted_value.get_restricted_value());
  }

  TEST(RestrictedValueTest, GetValueOutOfBounds) {
    auto restricted_value = RestrictedValue<unsigned long>(11u, 1u, 10u);
    EXPECT_THROW(restricted_value.get_restricted_value(), std::out_of_range);
  }
}
