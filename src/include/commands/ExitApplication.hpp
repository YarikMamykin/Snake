#ifndef SRC_INCLUDE_COMMANDS_EXITAPPLICATION_HPP
#define SRC_INCLUDE_COMMANDS_EXITAPPLICATION_HPP

#include "Command.hpp"
#include "Helper.hpp"

namespace commands {

  class ExitApplication : public Command {
    public:
      explicit ExitApplication() = default;
      ~ExitApplication () override = default;

      virtual DoSaveResult execute() override;
      virtual constexpr CommandID get_id() const override;
  };
}


#endif /* SRC_INCLUDE_COMMANDS_EXITAPPLICATION_HPP */
