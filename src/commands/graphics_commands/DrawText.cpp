#include "commands/graphics_commands/DrawText.hpp"
#include "xlib/XlibWrapper.hpp"

namespace commands {
  DrawText::DrawText(const std::string& text, const geometry::Point& top_left, const color::Color& color)
    : GraphicsCommand(geometry::Rectangle{.x = top_left.x, .y = top_left.y, .width = 0u, .height = 0u }, color)
    , text(text) {}

  void DrawText::execute() {
    xlib::XlibWrapper::self()->draw_text({rectangle.x, rectangle.y},color::Color(color),text);
  }


}
