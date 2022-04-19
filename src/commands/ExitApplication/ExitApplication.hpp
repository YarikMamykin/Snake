#pragma once
#include "commands/Command/Command.hpp"
#include "helpers/Helper.hpp"

namespace commands {

  class ExitApplication : public Command {
    public:
      explicit ExitApplication() = default;
      ~ExitApplication () override = default;

      virtual void execute(xlib::XProxy&) override;
  };
}



