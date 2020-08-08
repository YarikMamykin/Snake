#include "GameMenu.hpp"
#include <iostream>
#include <vector>

namespace views {


  GameMenu::Item::Item(bool active, const std::string& name, const XRectangle& frame) :
    left_text_margin(10) ,
    top_text_margin(10) {
      this->active = active;
      this->name = name;
      this->frame = frame;
    }

  void GameMenu::Item::show_text(xlib::X11_Window* x_window) {
    XSetForeground(x_window->x_display.display, 
        x_window->graphical_context, 
        x_window->win_sets.font_color);

    XDrawString(x_window->x_display.display, 
        x_window->window, 
        x_window->graphical_context, 
        this->frame.x + left_text_margin, 
        this->frame.y + (x_window->font_info->ascent + x_window->font_info->descent + top_text_margin / 2), 
        this->name.c_str(), 
        this->name.length());
  }

  void GameMenu::Item::show_frame(xlib::X11_Window* x_window) {
    this->frame.width = XTextWidth(x_window->font_info, this->name.c_str(), this->name.length()) + left_text_margin * 2;
    this->frame.height = x_window->font_info->ascent + x_window->font_info->descent + top_text_margin * 2;

    XSetLineAttributes(x_window->x_display.display, x_window->graphical_context,3,0,0,0);
    XSetForeground(x_window->x_display.display, x_window->graphical_context, ~0L);
    XDrawRectangle(x_window->x_display.display,
        x_window->window,
        x_window->graphical_context,
        this->frame.x,
        this->frame.y,
        this->frame.width,
        this->frame.height);
  }

  void GameMenu::Item::show(xlib::X11_Window* x_window) {
    this->show_text(x_window);
    this->show_frame(x_window);
  }

  int GameMenu::Item::get_width(xlib::X11_Window* x_window) const {
    return (XTextWidth(x_window->font_info, 
            this->name.c_str(), 
            this->name.length()) + left_text_margin * 2);
  }

  int GameMenu::Item::get_height(xlib::X11_Window* x_window) const {
    return (x_window->font_info->ascent + 
            x_window->font_info->descent + 
            top_text_margin * 2);
  }


  GameMenu::GameMenu(xlib::X11_Window* x_window) :
    x_window(x_window) {
      std::vector<std::string> item_names = { "New Game", "Score", "Settings", "Other blabla", "Exit" };
      for(auto i = 0, summary_height = 0; i < item_names.size(); ++i) {
        const auto&& x_pos = x_window->get_width() / 2 - XTextWidth(x_window->font_info, item_names[i].c_str(), item_names[i].length()) / 2;
        this->items.push_back(Item(false, item_names[i], { .x = x_pos, .y = x_window->get_height() / 3 + summary_height }));
        summary_height += items.back().get_height(x_window);
      }
    }

  GameMenu::~GameMenu() {
  }

  void GameMenu::activate() {
    for(auto& item : items) {
      item.show(x_window);
    }
  }

  void GameMenu::deactivate() {
  }

}
