#include "GameMenu.hpp"

namespace views {

  GameMenu::GameMenu() {
  }

  GameMenu::~GameMenu() {
  }

  void GameMenu::activate() {
    XSetForeground(x_display.display, graphical_context, win_sets.font_color);
    XDrawString(x_display.display, window, graphical_context, 50, 50, msg.c_str(), msg.length());

    XRectangle rectangle = {.x = 20, .y = 200, .width = 200, .height = 30};
    XSetForeground(x_display.display, graphical_context, win_sets.border_color);
    XFillRectangle(x_display.display, window, graphical_context, rectangle.x, rectangle.y, rectangle.width, rectangle.height);

    XSetForeground(x_display.display, graphical_context, 255L);
    XSetLineAttributes(x_display.display, graphical_context,5,0,0,0);
    XDrawRectangle(x_display.display, window, graphical_context, rectangle.x, rectangle.y, rectangle.width, rectangle.height);

    XSetForeground(x_display.display, graphical_context, ~0L);
    XSetLineAttributes(x_display.display, graphical_context,2,0,0,0);
    XDrawLine(x_display.display, window, graphical_context, 10,10,772,10);
  }

  void GameMenu::deactivate() {
  }

}
