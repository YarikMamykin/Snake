#pragma once

#include "commands/graphics_commands/GraphicsCommand.hpp"

namespace commands {
  class DrawRectangle : public GraphicsCommand {
    public:
      explicit DrawRectangle(const geometry::Rectangle& rectangle, const color::Color& color);
      virtual void execute(xlib::XProxy& proxy) override;
      virtual ~DrawRectangle() override = default;
  };
}

