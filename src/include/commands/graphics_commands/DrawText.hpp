#ifndef SRC_INCLUDE_COMMANDS_DRAWTEXT_HPP
#define SRC_INCLUDE_COMMANDS_DRAWTEXT_HPP

#include "GraphicsCommand.hpp"
#include <string>

namespace commands {
  class DrawText : public GraphicsCommand {
    protected:
      const std::string text;

    public:
      explicit DrawText(const std::string& text, const geometry::Point& top_left, const color::Color& color);
      virtual void execute() override;
      virtual ~DrawText() override = default;
  };
}

#endif /* SRC_INCLUDE_COMMANDS_DRAWTEXT_HPP */
