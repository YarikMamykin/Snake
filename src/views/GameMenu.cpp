#include "GameMenu.hpp"

namespace views {

  GameMenu::GameMenu(xlib::X11_Window* x_window) :
  x_window(x_window) {

  }

  GameMenu::~GameMenu() {
  }

  void GameMenu::activate() {
    XSetForeground(x_window->x_display.display, x_window->graphical_context, x_window->win_sets.font_color);
    XDrawString(x_window->x_display.display, x_window->window, x_window->graphical_context, 50, 50, x_window->msg.c_str(), x_window->msg.length());

    XRectangle rectangle = {.x = 20, .y = 200, .width = 200, .height = 30};
    XSetForeground(x_window->x_display.display, x_window->graphical_context, x_window->win_sets.border_color);
    XFillRectangle(x_window->x_display.display, x_window->window, x_window->graphical_context, rectangle.x, rectangle.y, rectangle.width, rectangle.height);

    XSetForeground(x_window->x_display.display, x_window->graphical_context, 255L);
    XSetLineAttributes(x_window->x_display.display, x_window->graphical_context,5,0,0,0);
    XDrawRectangle(x_window->x_display.display, x_window->window, x_window->graphical_context, rectangle.x, rectangle.y, rectangle.width, rectangle.height);

    XSetForeground(x_window->x_display.display, x_window->graphical_context, ~0L);
    XSetLineAttributes(x_window->x_display.display, x_window->graphical_context,2,0,0,0);
    XDrawLine(x_window->x_display.display, x_window->window, x_window->graphical_context, 10,10,772,10);
  }

  void GameMenu::deactivate() {
  }

}
