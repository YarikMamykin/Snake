#include "GameMenu.hpp"
#include <iostream>
#include <vector>
#include <algorithm>
#include "EventHandler.hpp"
#include "Helper.hpp"

namespace views {

  const unsigned int GameMenu::Item::left_text_margin = 10;
  const unsigned int GameMenu::Item::top_text_margin = 10;
  const unsigned int GameMenu::Item::frame_weight = 3;

  GameMenu::Item::Item(xlib::X11_Window* x_window, bool active, const std::string& name, const XRectangle& frame) :
  x_window(x_window) {
      this->active = active;
      this->name = name;
      this->frame = frame;
      this->frame.height = x_window->font_info->ascent + x_window->font_info->descent + top_text_margin * 2;
  }

  GameMenu::Item::~Item() {
  }

  void GameMenu::Item::show_text() const {
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

  void GameMenu::Item::show_frame() const {
    XSetLineAttributes(x_window->x_display.display, x_window->graphical_context,frame_weight,0,0,0);
    XSetForeground(x_window->x_display.display, x_window->graphical_context, ~0L);
    XDrawRectangle(x_window->x_display.display,
        x_window->window,
        x_window->graphical_context,
        this->frame.x,
        this->frame.y,
        this->frame.width,
        this->frame.height);
  }

  void GameMenu::Item::hide_frame() const {
    XSetLineAttributes(x_window->x_display.display, x_window->graphical_context,frame_weight,0,0,0);
    XSetForeground(x_window->x_display.display, x_window->graphical_context, 0L);
    XDrawRectangle(x_window->x_display.display,
        x_window->window,
        x_window->graphical_context,
        this->frame.x,
        this->frame.y,
        this->frame.width,
        this->frame.height);
  }

  void GameMenu::Item::show() const {
    this->show_text();
    if(!active) {
      this->hide_frame();
      return;
    } 
    this->show_frame();
  }

  void GameMenu::Item::show_focus() {
    this->show_text();
    this->show_frame();
    this->active = true;
  }

  void GameMenu::Item::hide_focus() {
    this->show_text();
    this->hide_frame();
    this->active = false;
  }

  bool GameMenu::Item::focused(const int& x, const int& y) const {
    return (x >= this->frame.x && (x <= this->frame.x + this->frame.width)) &&
           (y >= this->frame.y && (y <= this->frame.y + this->frame.height));
  }
  
  int GameMenu::Item::get_width() const {
    return (XTextWidth(x_window->font_info, 
          this->name.c_str(), 
          this->name.length()) + left_text_margin * 2);
  }

  int GameMenu::Item::get_height() const {
    return (x_window->font_info->ascent + 
        x_window->font_info->descent + 
        top_text_margin * 2);
  }

  void GameMenu::Item::handle_mouse_motion(const int& x, const int& y) {
    if(this->focused(x,y)) {
      this->show_focus();
    }
  }

  void GameMenu::Item::handle_button_press(const int& x, const int& y, const unsigned int& button) {
    if(this->focused(x,y)) {
      this->show_focus();
      if(button == Button1 && this->name == "Exit") {
        auto event = helpers::Helper::ConstructExitApplicationEvent(x_window);
        XSendEvent(x_window->x_display.display, x_window->window, true, NoEventMask, &event);
      }

      if(button == Button1 && this->name == "New Game") {
        auto event = helpers::Helper::ConstructChangeViewEvent(x_window, views::ViewID::MENU);
        XSendEvent(x_window->x_display.display, x_window->window, true, NoEventMask, &event);
      }
    }
  }

  GameMenu::GameMenu(xlib::X11_Window* x_window) :
    x_window(x_window) {
      std::vector<std::string> item_names = { "New Game", "Score", "Settings", "Other blabla", "Exit" };

      const auto max_item_name = std::max_element(item_names.begin(), item_names.end(), 
      [](const std::string& v1, const std::string& v2) {
        return v1.size() < v2.size();
      });

      const auto max_item_width = XTextWidth(x_window->font_info, max_item_name->c_str(), max_item_name->size()) + GameMenu::Item::left_text_margin * 2;
      const auto&& x_pos = x_window->get_width() / 2 - max_item_width / 2;
      auto summary_height = 0;

      for(auto& item_name : item_names) {
        this->items.push_back(Item(x_window, false, item_name, { .x = x_pos, .y = x_window->get_height() / 3 + summary_height + GameMenu::Item::frame_weight }));
        summary_height += items.back().get_height();
        items.back().frame.width = max_item_width;
      }

      items.begin()->show_focus();
      // for(std::list<Item>::iterator iterator = items.begin(); iterator != items.end(); ++iterator) {
        // auto iter_shift = iterator;
        // if(iter_shift != items.begin()) {
          // --iter_shift->next = &*iterator;
          // iterator->prev = &*iter_shift;
        // }
      // }

      // items.begin()->prev = &items.back();
      // items.begin()->next = &*std::next(items.begin(), 1);
      // items.back().next = &items.front();

      // for(auto& item : items) {
        // std::cout <<
          // std::boolalpha <<
          // (item.next ? true : false) <<
          // " " <<
          // (item.prev ? true : false) <<
          // std::endl;
      // }
    }

  GameMenu::~GameMenu() {
  }

  void GameMenu::activate() {
    this->update();
    for(auto& item : items) {
      item.hide_frame();
      item.show_text();
    }

    auto item_to_show = std::find_if(items.begin(), items.end(), [](const Item& item) { return item.active; });
    if(item_to_show != items.end()) {
      item_to_show->show();
    }
  }

  void GameMenu::update() {
    const auto&& x_pos = x_window->get_width() / 2 - items.begin()->frame.width / 2;
    auto summary_height = 0;

    for(auto& item : items) {
      item.frame.x = x_pos;
      item.frame.y = x_window->get_height() / 3 + summary_height + GameMenu::Item::frame_weight;
      summary_height += item.get_height();
    }
  }

  void GameMenu::deactivate() {
  }

  void GameMenu::handle_mouse_motion(const int& x, const int& y) {
    this->update();

    for(auto& item : items) {
      item.hide_focus();
    }

    for(auto& item : items) {
      item.handle_mouse_motion(x,y);
    }
  }

  void GameMenu::handle_button_press(const int& x, const int& y, const unsigned int& button) {
    this->update();

    for(auto& item : items) {
      item.hide_focus();
    }

    for(auto& item : items) {
      item.handle_button_press(x,y,button);
    }
  }

  void GameMenu::handle_key_press(const KeySym&& key_sym) {
    this->update();
    switch(key_sym) {
      case XK_Down:
        {
          const auto& active_item = std::find_if(items.begin(), items.end(), [](const Item& item) { return item.active; });
          for(auto& item : items) {
            item.hide_focus();
          }

          if(active_item == --items.end()) {
            items.begin()->show_focus();
            break;
          }

          std::next(active_item, 1)->show_focus();
          break;
        }
      case XK_Up:
        {
          auto active_item = std::find_if(items.begin(), items.end(), [](const Item& item) { return item.active; });
          for(auto& item : items) {
            item.hide_focus();
          }

          if(active_item == items.begin()) {
            items.back().show_focus();
            return;
          }

          std::prev(active_item, 1)->show_focus();
          break;
        }   
    }
  }
}
