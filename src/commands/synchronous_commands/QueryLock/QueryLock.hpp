#pragma once
#include <mutex>

namespace commands {

  class QueryLock {
    std::mutex m_m;
    std::lock_guard<std::mutex> m_lk;

    public:
      QueryLock();
      ~QueryLock();

      void unlock() noexcept;
  };
}
