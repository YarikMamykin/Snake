#ifndef SRC_INCLUDE_TIMING_TIMER_HPP
#define SRC_INCLUDE_TIMING_TIMER_HPP

#include <chrono>
#include <functional>
#include <future>
#include <thread>

namespace timing {
  struct Timer {
    std::atomic<bool> do_stop;
    std::function<void()> callback;
    std::chrono::milliseconds timeout;
    std::future<void> timer_thread;

    public:
    explicit Timer();
    explicit Timer(const std::chrono::milliseconds&& timeout, 
                   std::function<void()> callback = [](){});
    void launch(); 
    void stop();
    bool running() const;
  };
}

#endif /* SRC_INCLUDE_TIMING_TIMER_HPP */
