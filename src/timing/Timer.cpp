#include "Timer.hpp"

namespace timing {
  Timer::Timer(const std::chrono::milliseconds&& timeout, const TimerType&& type)
    : timeout(timeout)
      , type(type) {

      }
  void Timer::launch() {
    async_result = std::async([this]() {
      while(!do_stop.load() && type != TimerType::SingleShot) {
        std::this_thread::sleep_for(timeout);
        callback();
      }
    });
  }

  void Timer::stop() {
    do_stop.store(true);
  }

  bool Timer::running() const {
    return do_stop.load();
  }

}

