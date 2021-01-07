#include "gtest/gtest.h"
#include <string>
#include "ObservableValue.hpp"

namespace abstractions_testing {
  
  using namespace abstractions;

  TEST(ObservableValueTest, ChangeValue) {
    ObservableValue<int> observable_value(1000);
    EXPECT_EQ(1000, observable_value.get_value());
    for(auto i : {0,1,2,3,4,5,6,7,8,9}) {
      observable_value.change_value(i);
      EXPECT_EQ(i, observable_value.get_value());
    }
  }

  TEST(ObservableValueTest, ChangeValueNotifyUsers) {
    auto observable_value = std::make_shared<ObservableValue<int>>(1000);
    ASSERT_EQ(1000, observable_value->get_value());

    bool value_changed_callback_called = false;
    ObservableValueUser<int> observable_value_user(observable_value, [&value_changed_callback_called]() {
        value_changed_callback_called = true;
    });

    observable_value->change_value(1);
    EXPECT_EQ(1, observable_value->get_value());
    EXPECT_TRUE(value_changed_callback_called);
  }

  TEST(ObservableValueTest, OneUserChangesValueAnotherNotified) {
    auto observable_value = std::make_shared<ObservableValue<int>>(1000);
    ASSERT_EQ(1000, observable_value->get_value());

    ObservableValueUser<int> user1(observable_value);

    bool value_changed_user1_callback_called = false;
    bool value_changed_user2_callback_called = false;
    ObservableValueUser<int> user2(observable_value, [&value_changed_user2_callback_called]() {
        value_changed_user2_callback_called = true;
    });

    user1.change_value(1);
    EXPECT_EQ(1, observable_value->get_value());
    EXPECT_FALSE(value_changed_user1_callback_called);
    EXPECT_TRUE(value_changed_user2_callback_called);
  }

}

