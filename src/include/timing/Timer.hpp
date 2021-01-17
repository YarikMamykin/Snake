#ifndef SRC_INCLUDE_TIMING_TIMER_HPP
#define SRC_INCLUDE_TIMING_TIMER_HPP

#include <chrono>
#include <functional>
#include <future>
#include <thread>
#include "Constants.hpp"

namespace timing {
  struct Timer {
    std::chrono::milliseconds timeout;
    TimerType type;
    std::future<void> async_result;
    std::atomic<bool> do_stop;
    std::function<void()> callback;

    public:
    explicit Timer();
    explicit Timer(const std::chrono::milliseconds&& timeout, 
                   std::function<void()> callback = [](){},
                   const TimerType&& type = TimerType::Simple);
    void launch(); 
    void stop();
    void stop_async();
    bool running() const;
  };
}

#endif /* SRC_INCLUDE_TIMING_TIMER_HPP */
