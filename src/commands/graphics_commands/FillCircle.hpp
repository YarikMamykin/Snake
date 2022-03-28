#ifndef SRC_INCLUDE_COMMANDS_GRAPHICS_COMMANDS_FILLCIRCLE_HPP
#define SRC_INCLUDE_COMMANDS_GRAPHICS_COMMANDS_FILLCIRCLE_HPP

#include "commands/graphics_commands/GraphicsCommand.hpp"

namespace commands {
  class FillCircle : public GraphicsCommand {
    public:
      explicit FillCircle(const geometry::Rectangle& circle_frame, const color::Color& color);
      virtual void execute() override;
      virtual ~FillCircle() override = default;
  };
}

#endif /* SRC_INCLUDE_COMMANDS_GRAPHICS_COMMANDS_FILLCIRCLE_HPP */
