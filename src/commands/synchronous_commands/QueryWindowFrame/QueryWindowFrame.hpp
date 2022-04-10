#pragma once

#include "commands/synchronous_commands/SynchronousCommand.hpp"
#include "abstractions/ui/Object.hpp"

namespace commands {

  class QueryWindowFrame : public SynchronousCommand {
    protected:
      abstractions::ui::Object* window;

    public:
      explicit QueryWindowFrame(
          abstractions::ui::Object* window, 
          QueryLock& ql);
      ~QueryWindowFrame() override = default;

      virtual void execute(xlib::XProxy& proxy) override;
  };
}
