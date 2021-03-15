#ifndef SRC_INCLUDE_COMMANDS_FILLCIRCLE_HPP
#define SRC_INCLUDE_COMMANDS_FILLCIRCLE_HPP

#include "Command.hpp"

namespace commands {
  class FillCircle : public GraphicsCommand {
    public:
      explicit FillCircle(const geometry::Rectangle& circle_frame, const color::Color& color);
      virtual DoSaveResult execute() override;
      virtual constexpr CommandID get_id() const override;
      virtual ~FillCircle() override = default;
  };
}
#endif /* SRC_INCLUDE_COMMANDS_FILLCIRCLE_HPP */
