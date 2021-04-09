#ifndef SRC_INCLUDE_COMMANDS_GRAPHICS_COMMANDS_DRAWRECTANGLE_HPP
#define SRC_INCLUDE_COMMANDS_GRAPHICS_COMMANDS_DRAWRECTANGLE_HPP

#include "commands/graphics_commands/GraphicsCommand.hpp"

namespace commands {
  class DrawRectangle : public GraphicsCommand {
    public:
      explicit DrawRectangle(const geometry::Rectangle& rectangle, const color::Color& color);
      virtual void execute() override;
      virtual ~DrawRectangle() override = default;
  };
}

#endif /* SRC_INCLUDE_COMMANDS_GRAPHICS_COMMANDS_DRAWRECTANGLE_HPP */
