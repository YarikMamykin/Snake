#pragma once

#include "commands/Command/Command.hpp"
#include "types/enums/ViewID.hpp"

namespace commands {

  class ChangeView : public Command {
    protected:
      const views::ViewID viewID;

    public:
      explicit ChangeView(views::ViewID&& viewID);
      ~ChangeView() override = default;

      virtual void execute(xlib::XProxy&) override;
  };
}
