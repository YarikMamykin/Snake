#include "timing/Timer.hpp"

namespace {
  constexpr std::chrono::milliseconds no_wait(0u);
}

namespace timing {
  Timer::Timer(std::chrono::milliseconds timeout, std::function<void()> callback) 
  : m_timeout(timeout) 
  , m_callback(callback) { }

  Timer::~Timer() {
    this->stop();
  }

  void Timer::launch() noexcept {
    if(running()) 
      return;

    m_timer_thread = std::async(std::launch::async, 
        [
          timeout = this->m_timeout, 
          callback = this->m_callback,
          &cv = this->cv,
          &m = this->m
        ]() {

        std::unique_lock<std::mutex> lock(m);
        
        while(std::cv_status::timeout == cv.wait_for(lock, timeout)) { 

          callback(); 

        } 
    });
  }

  void Timer::stop() noexcept {
    if(!running())
      return;

    {
      std::lock_guard<std::mutex> lk(m);
    }
    cv.notify_one();

    m_timer_thread.wait();
  }

  bool Timer::running() const noexcept {

    try {

      return std::future_status::timeout == m_timer_thread.wait_for(no_wait);

    } catch(const std::future_error& err) {

      return false;

    }
  }
}

