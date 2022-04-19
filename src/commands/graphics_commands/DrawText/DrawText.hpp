#pragma once

#include "commands/graphics_commands/GraphicsCommand.hpp"
#include <string>

namespace commands {
  class DrawText : public GraphicsCommand {
    protected:
      const std::string text;

    public:
      explicit DrawText(const std::string& text, const geometry::Point& top_left, const color::Color& color);
      virtual void execute(xlib::XProxy&) override;
      virtual ~DrawText() override = default;
  };
}


