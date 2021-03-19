#ifndef SRC_INCLUDE_COMMANDS_FILLRECTANGLE_HPP
#define SRC_INCLUDE_COMMANDS_FILLRECTANGLE_HPP

#include "GraphicsCommand.hpp"

namespace commands {
  class FillRectangle : public GraphicsCommand {
    public:
      explicit FillRectangle(const geometry::Rectangle& rectangle, const color::Color& color);
      virtual void execute() override;
      virtual ~FillRectangle() override = default;
  };
}
#endif /* SRC_INCLUDE_COMMANDS_FILLRECTANGLE_HPP */
