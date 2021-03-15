#ifndef SRC_INCLUDE_COMMANDS_FILLRECTANGLE_HPP
#define SRC_INCLUDE_COMMANDS_FILLRECTANGLE_HPP

#include "Command.hpp"

namespace commands {
  class FillRectangle : public GraphicsCommand {
    public:
      explicit FillRectangle(const geometry::Rectangle& rectangle, const color::Color& color);
      virtual DoSaveResult execute() override;
      virtual constexpr CommandID get_id() const override;
      virtual ~FillRectangle() override = default;
  };
}
#endif /* SRC_INCLUDE_COMMANDS_FILLRECTANGLE_HPP */
