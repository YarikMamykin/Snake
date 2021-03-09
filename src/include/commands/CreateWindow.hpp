#ifndef SRC_INCLUDE_COMMANDS_CREATEWINDOW_HPP
#define SRC_INCLUDE_COMMANDS_CREATEWINDOW_HPP

#include "Command.hpp"

namespace commands {
  class CreateWindow : public Command {
    protected:
      color::COLOR_SCHEME_TYPE color_scheme;
      const char* name;

    public:
      explicit CreateWindow(geometry::Rectangle&& window_frame, color::COLOR_SCHEME_TYPE&& color_scheme, const char* name);
      virtual void execute() override;
      virtual ~CreateWindow() override = default;
  };
}


#endif /* SRC_INCLUDE_COMMANDS_CREATEWINDOW_HPP */
