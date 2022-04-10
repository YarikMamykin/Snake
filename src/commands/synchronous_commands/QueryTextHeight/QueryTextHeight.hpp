#pragma once

#include "commands/synchronous_commands/SynchronousCommand.hpp"
#include <string>

namespace commands {

  class QueryTextHeight : public SynchronousCommand {
    protected:
      unsigned int& height;

    public:
      explicit QueryTextHeight(unsigned int& result, QueryLock& ql);
      ~QueryTextHeight() override = default;

      virtual void execute(xlib::XProxy&) override;
  };
}
