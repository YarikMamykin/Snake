#ifndef SRC_INCLUDE_COMMANDS_COMMAND_HPP
#define SRC_INCLUDE_COMMANDS_COMMAND_HPP

#include "Rectangle.hpp" 
#include "Color.hpp"

namespace commands {
  class Command {
    protected:
      geometry::Rectangle rectangle;
      color::Color color;

      explicit Command(const geometry::Rectangle& rectangle, const color::Color& color);

    public:
      virtual void execute() = 0;
      virtual ~Command() {}
  };
}


#endif /* SRC_INCLUDE_COMMANDS_COMMAND_HPP */
