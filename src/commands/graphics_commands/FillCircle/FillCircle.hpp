#pragma once

#include "commands/graphics_commands/GraphicsCommand.hpp"

namespace commands {
  class FillCircle : public GraphicsCommand {
    public:
      explicit FillCircle(const geometry::Rectangle& circle_frame, const color::Color& color);
      virtual void execute(xlib::XProxy&) override;
      virtual ~FillCircle() override = default;
  };
}

