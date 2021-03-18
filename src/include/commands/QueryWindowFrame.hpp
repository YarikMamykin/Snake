#ifndef SRC_INCLUDE_COMMANDS_QUERYWINDOWFRAME_HPP
#define SRC_INCLUDE_COMMANDS_QUERYWINDOWFRAME_HPP

#include "Command.hpp"
#include "Object.hpp"

namespace commands {

  class QueryWindowFrame : public SynchronousCommand {
    protected:
      abstractions::ui::Object* window;

    public:
      explicit QueryWindowFrame(abstractions::ui::Object* window, std::atomic<bool>& trigger);
      ~QueryWindowFrame() override = default;

      virtual DoSaveResult execute() override;
      virtual constexpr CommandID get_id() const override;
  };
}


#endif /* SRC_INCLUDE_COMMANDS_QUERYWINDOWFRAME_HPP */
