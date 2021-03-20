#include "gtest/gtest.h"
#include "Timer.hpp"

namespace {
    const auto&& test_timeout = std::chrono::milliseconds(10u);
    auto empty_test_callback = [](){};
}

namespace timing_test {

TEST(TimerTest, CreationWithoutParams)
{
    timing::Timer t;
    EXPECT_TRUE(t.do_stop.load());
}

TEST(TimerTest, CreateWithParams)
{
    timing::Timer t(std::move(test_timeout), empty_test_callback);
    EXPECT_TRUE(t.do_stop.load());
}

TEST(TimerTest, LaunchSimple)
{
    auto test_value = 10;
    auto test_callback = [&test_value]() {
        test_value = 20;
    };

    timing::Timer t(std::move(test_timeout), test_callback);
    ASSERT_TRUE(t.do_stop.load());
    ASSERT_EQ(test_value, 10);
    t.launch();
    ASSERT_TRUE(t.running());
    std::this_thread::sleep_for(test_timeout + test_timeout * 0.1); // wait a little bit more than timer timeout
    t.stop();
    EXPECT_FALSE(t.running());
    EXPECT_EQ(test_value, 20);
}

}
