#ifndef SRC_INCLUDE_COMMANDS_QUERYWINDOWATTRIBUTES_HPP
#define SRC_INCLUDE_COMMANDS_QUERYWINDOWATTRIBUTES_HPP

#include "Command.hpp"

namespace commands {

  class QueryWindowAttributes : public Command {
    protected:
      XWindowAttributes attributes;

    public:
      explicit QueryWindowAttributes() = default;
      ~QueryWindowAttributes() override = default;

      virtual DoSaveResult execute() override;
      virtual constexpr CommandID get_id() const override;
      const XWindowAttributes& get_window_attributes() const;
  };
}

#endif /* SRC_INCLUDE_COMMANDS_QUERYWINDOWATTRIBUTES_HPP */
