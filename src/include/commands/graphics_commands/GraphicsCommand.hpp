#ifndef SRC_INCLUDE_COMMANDS_GRAPHICS_COMMAND_GRAPHICSCOMMAND_HPP
#define SRC_INCLUDE_COMMANDS_GRAPHICS_COMMAND_GRAPHICSCOMMAND_HPP

#include "Rectangle.hpp" 
#include "Color.hpp"
#include "Command.hpp" 

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



#endif /* SRC_INCLUDE_COMMANDS_GRAPHICS_COMMAND_GRAPHICSCOMMAND_HPP */
