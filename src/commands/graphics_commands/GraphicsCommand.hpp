#ifndef SRC_INCLUDE_COMMANDS_GRAPHICS_COMMANDS_GRAPHICSCOMMAND_HPP
#define SRC_INCLUDE_COMMANDS_GRAPHICS_COMMANDS_GRAPHICSCOMMAND_HPP

#include "geometry/Rectangle.hpp" 
#include "color/Color/Color.hpp"
#include "commands/Command/Command.hpp" 

namespace commands {

  class GraphicsCommand : public Command {
    protected:
      geometry::Rectangle rectangle;
      color::Color color;

      explicit GraphicsCommand (const geometry::Rectangle& rectangle, const color::Color& color) 
      : rectangle(rectangle), color(color) { }
    public: 
      virtual ~GraphicsCommand() override = default;
  };
}




#endif /* SRC_INCLUDE_COMMANDS_GRAPHICS_COMMANDS_GRAPHICSCOMMAND_HPP */
