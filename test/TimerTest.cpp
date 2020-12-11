#include "gtest/gtest.h"
#include "Timer.hpp"

namespace {
    const auto&& test_timeout = std::chrono::milliseconds(10u);
    auto empty_test_callback = [](){};
    const auto&& test_timer_type_simple = timing::TimerType::Simple;
    const auto&& test_timer_type_singleshot = timing::TimerType::SingleShot;
}

namespace timing_test {

TEST(TimerTest, CreationWithoutParams)
{
    timing::Timer t;
    EXPECT_TRUE(t.do_stop.load());
    EXPECT_EQ(t.type, test_timer_type_simple);
}

TEST(TimerTest, CreateWithParams)
{
    timing::Timer t(std::move(test_timeout), empty_test_callback, std::move(test_timer_type_singleshot));
    EXPECT_TRUE(t.do_stop.load());
    EXPECT_EQ(t.type, test_timer_type_singleshot);
}

TEST(TimerTest, LaunchSingleShot)
{
    auto test_value = 10;
    auto test_callback = [&test_value]() {
        test_value = 20;
    };

    timing::Timer t(std::move(test_timeout), test_callback, std::move(test_timer_type_singleshot));
    ASSERT_TRUE(t.do_stop.load());
    ASSERT_EQ(t.type, test_timer_type_singleshot);
    ASSERT_EQ(test_value, 10);
    t.launch();
    ASSERT_TRUE(t.running());
    std::this_thread::sleep_for(test_timeout + test_timeout * 0.1); // wait a little bit more than timer timeout
    EXPECT_FALSE(t.running());
    EXPECT_EQ(test_value, 20);
}

TEST(TimerTest, LaunchSimple)
{
    auto test_value = 10;
    auto test_callback = [&test_value]() {
        test_value = 20;
    };

    timing::Timer t(std::move(test_timeout), test_callback, std::move(test_timer_type_simple));
    ASSERT_TRUE(t.do_stop.load());
    ASSERT_EQ(t.type, test_timer_type_simple);
    ASSERT_EQ(test_value, 10);
    t.launch();
    ASSERT_TRUE(t.running());
    std::this_thread::sleep_for(test_timeout + test_timeout * 0.1); // wait a little bit more than timer timeout
    t.stop();
    EXPECT_FALSE(t.running());
    EXPECT_EQ(test_value, 20);
}

TEST(TimerTest, StopAsync)
{
    timing::Timer t(std::move(test_timeout), empty_test_callback, std::move(test_timer_type_simple));
    ASSERT_TRUE(t.do_stop.load());
    ASSERT_EQ(t.type, test_timer_type_simple);
    t.launch();
    ASSERT_TRUE(t.running());
    std::this_thread::sleep_for(test_timeout + test_timeout * 0.1); // wait a little bit more than timer timeout
    t.stop_async();
    EXPECT_FALSE(t.running());
}
}
