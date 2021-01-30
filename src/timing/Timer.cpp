#include "Timer.hpp"

namespace timing {
  Timer::Timer()
  : do_stop(true)
  , type(TimerType::Simple) {

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
    if(running()) return;

    do_stop.store(false);

    async_result = std::async([this]() {
        using namespace std::chrono;
        auto start_point = steady_clock::now();

        switch(this->type) {
          case TimerType::Simple: { 
            while(!do_stop.load()) { 
              if(duration_cast<milliseconds>(steady_clock::now() - start_point) >= timeout) {
                callback(); 
                start_point = steady_clock::now();
              }
            } 
            break;
          }

          case TimerType::SingleShot: { 
            while(!do_stop.load()) {
              if(duration_cast<milliseconds>(steady_clock::now() - start_point) >= timeout) {
                callback(); 
                do_stop.store(true);
              }
            }
            break;
          }
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

