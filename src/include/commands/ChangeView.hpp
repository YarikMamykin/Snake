#ifndef SRC_INCLUDE_COMMANDS_CHANGEVIEW_HPP
#define SRC_INCLUDE_COMMANDS_CHANGEVIEW_HPP

#include "Command.hpp"
#include "View.hpp"

namespace commands {

  class ChangeView : public Command {
    protected:
      const views::ViewID viewID;

    public:
      explicit ChangeView(views::ViewID&& viewID);
      ~ChangeView() override = default;

      virtual DoSaveResult execute() override;
      virtual constexpr CommandID get_id() const override;
  };
}

#endif /* SRC_INCLUDE_COMMANDS_CHANGEVIEW_HPP */
