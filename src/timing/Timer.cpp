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
    do_stop.store(false);
    async_result = std::async([this]() {
        switch(this->type) {
          case TimerType::Simple: { 
            while(!do_stop.load()) { 
              std::this_thread::sleep_for(timeout); 
              if(do_stop.load()) { 
                break; 
              } 
              callback(); 
            } 
          }

          case TimerType::SingleShot: { 
              std::this_thread::sleep_for(timeout); 
              callback(); 
              do_stop.store(true);
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

