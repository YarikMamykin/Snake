#include "gtest/gtest.h"
#include "timing/Timer.hpp"
#include <mutex>
#include <condition_variable>
#include <chrono>

namespace {
    const auto&& test_timeout = std::chrono::milliseconds(10u);
    const std::chrono::milliseconds time_to_wait (std::chrono::duration_cast<std::chrono::milliseconds>(test_timeout + test_timeout * 0.1));
    auto empty_test_callback = [](){};
}

namespace timing_test {

TEST(TimerTest, LaunchSimple)
{
    auto test_value = 10;
    auto test_callback = [&test_value]() {
        test_value = 20;
    };

    timing::Timer t(std::move(test_timeout), test_callback);

    ASSERT_FALSE(t.running());
    ASSERT_EQ(test_value, 10);

    t.launch();
    
    ASSERT_TRUE(t.running());

    std::mutex m;
    std::unique_lock<std::mutex> lk(m);
    std::condition_variable cv;
    cv.wait_for(lk, time_to_wait); // wait a little bit more than timer timeout

    t.stop();

    EXPECT_FALSE(t.running());
    EXPECT_EQ(test_value, 20);
}

}
