#include "ExitApplication.hpp"
#include "Helper.hpp"

namespace commands {

  void ExitApplication::execute() {
    helpers::Helper::SendExitApplicationEvent();
  }

}

