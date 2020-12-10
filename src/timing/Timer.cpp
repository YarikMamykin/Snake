#include "Timer.hpp"

namespace timing {
  Timer::Timer()
  : type(TimerType::Simple) {

  }

  Timer::Timer(const std::chrono::milliseconds&& timeout, 
               std::function<void()> callback,
               const TimerType&& type)
  : timeout(timeout)
  , callback(callback)
  , do_stop(true)
  , type(type) {

  }

  void Timer::launch() {
    do_stop.store(false);
    async_result = std::async([this]() {
      while(type != TimerType::SingleShot) {
        std::this_thread::sleep_for(timeout);
        if(do_stop.load()) {
          break;
        }
        callback();
      }
    });
  }

  void Timer::stop() {
    do_stop.store(true);
    async_result.wait();
  }

  void Timer::stop_async() {
    do_stop.store(true);
  }

  bool Timer::running() const {
    return !do_stop.load();
  }
}

