#include "commands/ExitApplication.hpp"
#include "helpers/Helper.hpp"

namespace commands {

  void ExitApplication::execute(xlib::XProxy&) {
    helpers::Helper::SendExitApplicationEvent();
  }

}

