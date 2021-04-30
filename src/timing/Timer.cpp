#include "timing/Timer.hpp"

namespace timing {
  Timer::Timer()
  : do_stop(true) { }

  Timer::Timer(const std::chrono::milliseconds&& timeout, 
               std::function<void()> callback)
  : timeout(timeout)
  , callback(callback)
  , do_stop(true) { }

  Timer::~Timer() {
    this->stop();
  }

  void Timer::launch() {
    if(running()) return;

    do_stop.store(false);

    timer_thread = std::async(std::launch::async, [this]() {
      using namespace std::chrono;
      auto start_point = steady_clock::now();

      while(!do_stop.load()) { 
        if(duration_cast<milliseconds>(steady_clock::now() - start_point) >= timeout) {
          callback(); 
          start_point = steady_clock::now();
        }
        std::this_thread::sleep_for(decltype(timeout)(1u)); // if it sleeps, CPU works less
      } 
    });
  }

  void Timer::stop() {
    if(running()) {
      do_stop.store(true);
      timer_thread.wait();
    }
  }

  bool Timer::running() const {
    return !do_stop.load();
  }
}

