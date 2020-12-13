#include "GameMenu.hpp"
#include <iostream>
#include <vector>
#include <algorithm>
#include <tuple>
#include "EventHandler.hpp"
#include "Helper.hpp"

namespace {
  const std::string NewGameItemName = "New Game"; 
  const std::string ScoreItemName = "Score"; 
  const std::string SettingsItemName = "Settings"; 
  const std::string ExitItemName = "Exit";

  auto empty_mouse_motion_handler = [](const int& x, const int& y) {};
  auto empty_mouse_button_press_handler = [](const int& x, const int& y, const unsigned int& button) {};
  auto empty_key_press_handler = [](const KeySym&& key_sym) {};
}

namespace views {

  const unsigned int GameMenu::Item::left_text_margin = 10;
  const unsigned int GameMenu::Item::top_text_margin = 10;
  const unsigned int GameMenu::Item::frame_weight = 3;

  GameMenu::Item::Item(xlib::X11_Window* x_window, 
      bool active, 
      const std::string& name, 
      const geometry::Rectangle& frame,
      MOUSE_MOTION_HANDLER_TYPE mouse_motion_handler,
      MOUSE_BUTTON_PRESS_HANDLER_TYPE mouse_button_press_handler,
      KEY_PRESS_HANDLER_TYPE key_press_handler)
  :x_window(x_window)
  ,mouse_button_press_handler(mouse_button_press_handler) 
  ,mouse_motion_handler(mouse_motion_handler) 
  ,key_press_handler(key_press_handler) {
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
      this->mouse_motion_handler(x,y);
    }
  }

  void GameMenu::Item::handle_button_press(const int& x, const int& y, const unsigned int& button) {
    if(this->active) {
      this->show_focus();
      if(button == Button1) {
        this->mouse_button_press_handler(x,y,button);
      }
    }
  }

  void GameMenu::Item::handle_key_press(const KeySym&& key_sym) {
    if(!this->active) {
      return;
    }

    this->key_press_handler(std::move(key_sym));
  }

  GameMenu::GameMenu(xlib::X11_Window* x_window) :
    x_window(x_window) {
      Item::ITEMS_EVENT_HANDLERS_VECTOR_TYPE items_event_handlers = {
        {
          NewGameItemName,
          empty_mouse_motion_handler,
          [](const int& x, const int& y, const unsigned int& button) {
          },
          [x_window](const KeySym&& key_sym) {
            switch(key_sym) {
              case XK_Return: helpers::Helper::SendChangeViewEvent(x_window, views::ViewID::ACTION); break;
            }
          }
        },
        {
          ScoreItemName,
          empty_mouse_motion_handler,
          empty_mouse_button_press_handler,
          empty_key_press_handler
        },
        {
          SettingsItemName,
          empty_mouse_motion_handler,
          empty_mouse_button_press_handler,
          empty_key_press_handler
        },
        {
          ExitItemName,
          empty_mouse_motion_handler,
          empty_mouse_button_press_handler,
          [x_window](const KeySym&& key_sym) {
            switch(key_sym) {
              case XK_Return: helpers::Helper::SendExitApplicationEvent(x_window); break;
            }
          }
        },
      };

      const auto&& item_with_longest_name = std::max_element(items_event_handlers.begin(), items_event_handlers.end(), 
      [](const Item::ITEMS_EVENT_HANDLERS_TYPE& item1, const Item::ITEMS_EVENT_HANDLERS_TYPE& item2) {
        return std::get<0>(item1).size() < std::get<0>(item2).size();
      });
      const auto& item_longest_name = std::get<0>(*item_with_longest_name);

      const auto max_item_width = XTextWidth(x_window->font_info, item_longest_name.c_str(), item_longest_name.size()) + GameMenu::Item::left_text_margin * 2;
      const auto&& x_pos = x_window->get_width() / 2 - max_item_width / 2;

      auto summary_height = 0;
      const bool active = false;
      for(auto& item : items_event_handlers) {
        this->items.emplace_back(
            Item(x_window, 
              active, 
              std::get<0>(item),
              { 
                .x = x_pos, 
                .y = x_window->get_height() / 3 + summary_height + GameMenu::Item::frame_weight,
                .width = max_item_width 
              },
              std::get<1>(item),
              std::get<2>(item),
              std::get<3>(item)
        ));
        summary_height += items.back().get_height();
      }

      std::for_each(items.begin(), items.end(), [](const Item& item) { item.show(); });
      items.begin()->show_focus();
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

          std::next(active_item)->show_focus();
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

          std::prev(active_item)->show_focus();
          break;
        }   
      case XK_Return:
        {
          for(auto& item : items) {
            item.handle_key_press(std::move(key_sym));
          }
          break;
        }
    }
  }

  const int GameMenu::get_event_handling_mask() const {
    return events::KeyPressHandler::mask | events::MouseMotionHandler::mask | events::MouseButtonPressHandler::mask;
  }
}
