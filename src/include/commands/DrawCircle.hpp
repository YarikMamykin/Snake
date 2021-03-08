#ifndef SRC_INCLUDE_COMMANDS_DRAWCIRCLE_HPP
#define SRC_INCLUDE_COMMANDS_DRAWCIRCLE_HPP

#include "Command.hpp"

namespace commands {
  class DrawCircle : public Command {
    public:
      explicit DrawCircle(const geometry::Rectangle& circle_frame, const color::Color& color);
      virtual void execute() override;
      virtual ~DrawCircle() override = default;
  };
}
#endif /* SRC_INCLUDE_COMMANDS_DRAWCIRCLE_HPP */
