#ifndef SRC_INCLUDE_COMMANDS_DRAWRECTANGLE_HPP
#define SRC_INCLUDE_COMMANDS_DRAWRECTANGLE_HPP

#include "Command.hpp"

namespace commands {
  class DrawRectangle : public GraphicsCommand {
    public:
      explicit DrawRectangle(const geometry::Rectangle& rectangle, const color::Color& color);
      virtual DoSaveResult execute() override;
      virtual constexpr CommandID get_id() const override;
      virtual ~DrawRectangle() override = default;
  };
}
#endif /* SRC_INCLUDE_COMMANDS_DRAWRECTANGLE_HPP */
