#ifndef SRC_INCLUDE_COMMANDS_SYNCHRONOUS_COMMANDS_QUERYWINDOWFRAME_HPP
#define SRC_INCLUDE_COMMANDS_SYNCHRONOUS_COMMANDS_QUERYWINDOWFRAME_HPP

#include "commands/synchronous_commands/SynchronousCommand.hpp"
#include "abstractions/ui/Object.hpp"

namespace commands {

  class QueryWindowFrame : public SynchronousCommand {
    protected:
      abstractions::ui::Object* window;

    public:
      explicit QueryWindowFrame(abstractions::ui::Object* window, std::atomic<bool>& trigger);
      ~QueryWindowFrame() override = default;

      virtual void execute(xlib::XProxy& proxy) override;
  };
}



#endif /* SRC_INCLUDE_COMMANDS_SYNCHRONOUS_COMMANDS_QUERYWINDOWFRAME_HPP */
