#include "ExitApplication.hpp"
#include "Helper.hpp"

namespace commands {

  DoSaveResult ExitApplication::execute() {
    helpers::Helper::SendExitApplicationEvent();
    return DoSaveResult::NO;
  }

  /* constexpr */ CommandID ExitApplication::get_id() const {
    return CommandID::ExitApplication;
  }
}

