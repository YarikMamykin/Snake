#include "QueryLock.hpp"
#include <mutex>


namespace commands {

  QueryLock::QueryLock() 
  : m_lk(m_m) { }

  QueryLock::~QueryLock() {
    std::unique_lock lk(m_m);
  }

  void QueryLock::unlock() noexcept {
    m_m.unlock();
  }

}
