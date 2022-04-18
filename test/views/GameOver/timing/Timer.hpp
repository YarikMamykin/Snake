#pragma once

#include <chrono>
#include <future>
#include <gmock/gmock.h>

namespace timing {
  class Timer {

    public:
      explicit Timer(
          std::chrono::milliseconds timeout, 
          std::function<void()> callback) {}
      ~Timer() = default;

      MOCK_METHOD(void, launch, (), (noexcept));
  };
}
