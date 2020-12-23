#ifndef SRC_INCLUDE_ABSTRACTIONS_HORIZONTALRECTIFIER_HPP
#define SRC_INCLUDE_ABSTRACTIONS_HORIZONTALRECTIFIER_HPP

#include <list>
#include <functional>
#include <algorithm>
#include <iostream>
#include "Constants.hpp"
#include "Point.hpp"

namespace ui {

  template <class Object, LayoutType layout_type>
    class AlignHandler {
      private:
        geometry::Point top_left;
        std::list<Object*> objects;
        const unsigned int spacing;

        struct ElementsWidthRectifier {
        };

        struct ElementsHeightRectifier {
        };

      public:
        AlignHandler(const geometry::Point& top_left, const unsigned int& spacing = 20U) 
        : top_left(top_left)
        , spacing(spacing) { }

        void add(Object* object) {
          objects.push_back(object);
          align_objects();
        }

        void update() {
          for(auto& object : objects) {
            object->show();
          }
        }

        const int get_x() const {
          return top_left.x;
        }

        const int get_y() const {
          return top_left.y;
        }

        const unsigned int get_width() const {
          switch(layout_type) {
            case LayoutType::VERTICAL: 
              {
                auto widest = *std::max_element(objects.begin(), objects.end(), [](Object* object1, Object* object2) { return object1->get_width() > object2->get_width(); }); 
                return widest->get_width();
              }

            case LayoutType::HORIZONTAL: 
              {
                return objects.back()->get_x() + objects.back()->get_width() - top_left.x;
              }
          }
        }

        const unsigned int get_height() const {
          switch(layout_type) {
            case LayoutType::HORIZONTAL: 
              {
                auto highest = *std::max_element(objects.begin(), objects.end(), [](Object* object1, Object* object2) { return object1->get_height() > object2->get_height(); }); 
                return highest->get_height();
              }

            case LayoutType::VERTICAL: 
              {
                return objects.back()->get_y() + objects.back()->get_height() - top_left.y;
              }
          }
        }

      private:
        typedef std::function<void (decltype(objects.begin())& )> ALIGN_HANDLER_TYPE;

        void align_horizontally(decltype(objects.begin())& objects_iter) {
          auto& prev_object = *std::prev(objects_iter);
          const auto&& prev_x = prev_object->get_x();
          const auto&& prev_width = prev_object->get_width();
          (*objects_iter)->set_position(prev_x + prev_width + spacing, top_left.y);
        }

        void align_vertically(decltype(objects.begin())& objects_iter) {
          auto& prev_object = *std::prev(objects_iter);
          const auto&& prev_y = prev_object->get_y();
          const auto&& prev_height = prev_object->get_height();
          (*objects_iter)->set_position(top_left.x, prev_y + prev_height + spacing);
        }

        void align_objects() {
          auto objects_iter = objects.begin();
          (*objects_iter)->set_position(top_left.x, top_left.y);
          if(1u == objects.size()) {
            return;
          }

          ALIGN_HANDLER_TYPE align_handler;

          switch(layout_type) {
            case LayoutType::HORIZONTAL: align_handler = std::move(std::bind(&AlignHandler<Object, layout_type>::align_horizontally, this, std::placeholders::_1)); break;
            case LayoutType::VERTICAL: align_handler = std::move(std::bind(&AlignHandler<Object, layout_type>::align_vertically, this, std::placeholders::_1)); break;
          }

          while((objects_iter = std::next(objects_iter)) != objects.end()) {
            align_handler(objects_iter);
          }
        }
    };
}

#endif /* SRC_INCLUDE_ABSTRACTIONS_HORIZONTALRECTIFIER_HPP */
