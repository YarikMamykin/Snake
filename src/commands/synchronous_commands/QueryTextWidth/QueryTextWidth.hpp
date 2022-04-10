#pragma once

#include "commands/synchronous_commands/SynchronousCommand.hpp"
#include <string>

namespace commands {

  class QueryTextWidth : public SynchronousCommand {
    protected:
      const std::string& text;
      unsigned int& width;

    public:
      explicit QueryTextWidth(const std::string& text, 
                              unsigned int& result,
                              QueryLock& ql);
      ~QueryTextWidth() override = default;

      virtual void execute(xlib::XProxy&) override;
  };
}
