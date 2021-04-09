#include "commands/ExitApplication.hpp"
#include "helpers/Helper.hpp"

namespace commands {

  void ExitApplication::execute() {
    helpers::Helper::SendExitApplicationEvent();
  }

}

