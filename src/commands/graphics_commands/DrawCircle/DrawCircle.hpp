#pragma once

#include "commands/graphics_commands/GraphicsCommand.hpp"

namespace commands {
  class DrawCircle : public GraphicsCommand {
    public:
      explicit DrawCircle(const geometry::Rectangle& circle_frame, const color::Color& color);
      virtual void execute(xlib::XProxy&) override;
      virtual ~DrawCircle() override = default;
  };
}

