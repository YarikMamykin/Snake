#ifndef SRC_INCLUDE_COMMANDS_CHANGEVIEW_HPP
#define SRC_INCLUDE_COMMANDS_CHANGEVIEW_HPP

#include "Command.hpp"
#include "Constants.hpp"

namespace commands {

  class ChangeView : public Command {
    protected:
      const views::ViewID viewID;

    public:
      explicit ChangeView(views::ViewID&& viewID);
      ~ChangeView() override = default;

      virtual void execute() override;
  };
}

#endif /* SRC_INCLUDE_COMMANDS_CHANGEVIEW_HPP */
