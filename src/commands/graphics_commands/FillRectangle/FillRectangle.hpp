#pragma once

#include "commands/graphics_commands/GraphicsCommand.hpp"

namespace commands {
  class FillRectangle : public GraphicsCommand {
    public:
      explicit FillRectangle(const geometry::Rectangle& rectangle, const color::Color& color);
      virtual void execute(xlib::XProxy&) override;
      virtual ~FillRectangle() override = default;
  };
}

