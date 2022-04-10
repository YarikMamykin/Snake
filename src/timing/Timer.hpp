#pragma once

#include <chrono>
#include <future>
#include <mutex>
#include <condition_variable>

namespace timing {
  class Timer {
    std::chrono::milliseconds m_timeout;
    std::function<void()> m_callback;
    std::future<void> m_timer_thread;

    std::mutex m;
    std::condition_variable cv;

    public:
      explicit Timer(std::chrono::milliseconds timeout, std::function<void()> callback);
      ~Timer();

      void launch() noexcept; 
      void stop() noexcept;
      bool running() const noexcept;
  };
}
