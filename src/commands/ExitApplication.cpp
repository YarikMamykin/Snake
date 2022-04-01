#include "commands/ExitApplication.hpp"
#include "helpers/Helper.hpp"

namespace commands {

  void ExitApplication::execute(xlib::XProxy& proxy) {
    helpers::Helper::SendExitApplicationEvent(proxy);
  }

}

