#pragma once

#include "commands/Command/Command.hpp" 
#include <commands/synchronous_commands/QueryLock/QueryLock.hpp>

namespace commands {

  class SynchronousCommand : public Command {
    protected:
      QueryLock& m_ql;

      explicit SynchronousCommand(QueryLock& ql) 
      : m_ql(ql) { }

    public:
      virtual ~SynchronousCommand() override {
        m_ql.unlock();
      }
  };
}
