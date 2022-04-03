#pragma once

#include "abstractions/ui/Object.hpp"
#include "types/enums/LayoutType.hpp"
#include <list>
#include <algorithm>
#include <memory>
#include <numeric>
#include <iostream>

namespace abstractions::ui {

  class Menu : public Object {

    protected:
      std::list<std::unique_ptr<Object>> items;
      std::list<std::unique_ptr<Object>>::iterator current_item;
      ::ui::LayoutType items_layout;
      const unsigned int spacing;

      Menu(const ::ui::LayoutType& layout, 
          const geometry::Rectangle& frame, 
          const color::COLOR_SCHEME_TYPE& color_scheme, 
          const unsigned int& spacing = 20U) 
        : Object(frame, color_scheme) 
          , current_item(items.end())
          , items_layout(layout) 
          , spacing(spacing) { }


      const unsigned int update_menu_height() const {
        switch(items_layout) {
          case ::ui::LayoutType::HORIZONTAL:
            {
              auto max_element_predicate = [](const std::unique_ptr<Object>& object1, const std::unique_ptr<Object>& object2) 
              { return object1->get_height() < object2->get_height(); };
              auto highest = std::max_element(items.begin(), items.end(), max_element_predicate);
              return highest->get()->get_height();
            }

          case ::ui::LayoutType::VERTICAL:
            {
              unsigned int summary_height = 0U;
              for(auto& item : items) {
                summary_height += item->get_height();
              } 
              return summary_height + spacing * (items.size()-1u);
            }
        } 
        return 0U;
      }

      const unsigned int update_menu_width() const {
        switch(items_layout) {
          case ::ui::LayoutType::VERTICAL:
            {
              auto max_element_predicate = [](const std::unique_ptr<Object>& object1, const std::unique_ptr<Object>& object2) 
              { return object1->get_width() < object2->get_width(); };
              auto widest = std::max_element(items.begin(), items.end(), max_element_predicate);
              return widest->get()->get_width();
            }
          case ::ui::LayoutType::HORIZONTAL:              
            {
              unsigned int summary_width = 0U;
              for(auto& item : items) {
                summary_width += item->get_width();
              } 
              return summary_width + spacing * (items.size()-1u);
            }
        }
        return 0U;
      }

      void update_menu_frame() {
        this->frame.width = update_menu_width();
        this->frame.height = update_menu_height();
      }

    public:
      virtual void add_item(std::unique_ptr<Object> item) {
        items.emplace_back(std::move(item));
        if(items.size() == 1U) {
          items.front()->set_position(this->frame.x, this->frame.y);
          current_item = items.begin();
        } else {
          switch(items_layout) {
            case ::ui::LayoutType::HORIZONTAL: 
              {
                auto prev_item_ptr = std::prev(items.end(), 2)->get();
                items.back()->set_position(prev_item_ptr->get_x() + prev_item_ptr->get_width() + spacing, this->frame.y);
                break;
              }
            case ::ui::LayoutType::VERTICAL: 
              {
                auto prev_item_ptr = std::prev(items.end(), 2)->get();
                items.back()->set_position(this->frame.x, prev_item_ptr->get_y() + prev_item_ptr->get_height() + spacing);
                break;
              }
          }
        }
        update_menu_frame();
      }

      virtual void show(bool show_flag) override {
        ObjectsLayoutPositioner(items_layout, this->items, spacing);
        for(auto& item : items) {
          item->show(show_flag);
        }
        if(current_item != items.end()) {
          current_item->get()->show(true);
        }
      }

      virtual void show_frame(bool) override { }

      virtual void set_position(const int& x, const int& y) override {
        this->frame.set_position(x,y);
        items.front()->set_position(x,y);
      }

      virtual void set_center(const int& x, const int& y) override {
        this->frame.set_center(x,y);
        items.front()->set_position(this->frame.x, this->frame.y);
      }

      virtual void move_to_next_item() {
        for(auto& item : items) {
          item->set_focused(false);
        }

        if(current_item == std::prev(items.end())) {
          current_item = items.begin();
          return;
        }

        current_item = std::next(current_item);
        return;
      }

      virtual void move_to_prev_item() {
        for(auto& item : items) {
          item->set_focused(false);
        }

        if(current_item == items.begin()) {
          current_item = std::prev(items.end());
          return;
        }

        current_item = std::prev(current_item);
        return;
      }

      decltype(current_item) get_current_item() const { return current_item; }

    public:
      struct ObjectsLayoutPositioner {
        ObjectsLayoutPositioner(const ::ui::LayoutType layout, decltype(Menu::items)& objects, const unsigned int spacing = 20U) {
          switch(layout) {
            case ::ui::LayoutType::VERTICAL: position_vertically(objects, spacing); break;
            case ::ui::LayoutType::HORIZONTAL: position_horizontally(objects, spacing); break;
          }
        }

        private:
        void position_vertically(decltype(Menu::items)& objects, const unsigned int spacing) {
          decltype(Menu::current_item) items_iterator = objects.begin();
          while((items_iterator = std::next(items_iterator)) != objects.end()) {
            auto prev_item = std::prev(items_iterator);
            items_iterator->get()->set_position(
                objects.begin()->get()->get_x(), 
                prev_item->get()->get_y() + prev_item->get()->get_height() + spacing);
          }
        }

        void position_horizontally(decltype(Menu::items)& objects, const unsigned int spacing) {
          decltype(Menu::current_item) items_iterator = objects.begin();
          while((items_iterator = std::next(items_iterator)) != objects.end()) {
            auto prev_item = std::prev(items_iterator);
            items_iterator->get()->set_position(
                prev_item->get()->get_x() + prev_item->get()->get_width() + spacing,
                objects.begin()->get()->get_y()); 
          }
        }
      };

      virtual ~Menu() {};
  };
}
