#ifndef SRC_INCLUDE_COMMANDS_EXITAPPLICATION_HPP
#define SRC_INCLUDE_COMMANDS_EXITAPPLICATION_HPP
#include "abstractions/commands/Command.hpp"
#include "helpers/Helper.hpp"

namespace commands {

  class ExitApplication : public Command {
    public:
      explicit ExitApplication() = default;
      ~ExitApplication () override = default;

      virtual void execute() override;
  };
}



#endif /* SRC_INCLUDE_COMMANDS_EXITAPPLICATION_HPP */
