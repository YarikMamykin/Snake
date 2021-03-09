#ifndef SRC_INCLUDE_COMMANDS_DESTROYWINDOW_HPP
#define SRC_INCLUDE_COMMANDS_DESTROYWINDOW_HPP

#include "Command.hpp"

namespace commands {
  class DestroyWindow : public Command {
    public:
      explicit DestroyWindow();
      virtual void execute() override;
      virtual ~DestroyWindow() override = default;
  };
}



#endif /* SRC_INCLUDE_COMMANDS_DESTROYWINDOW_HPP */
