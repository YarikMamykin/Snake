#ifndef SRC_INCLUDE_INTERFACES_OBJECT_HPP
#define SRC_INCLUDE_INTERFACES_OBJECT_HPP

#include "Rectangle.hpp"
#include "Constants.hpp"
#include "Color.hpp"

namespace abstractions {
  namespace ui {

    class Object {
      protected:
        geometry::Rectangle frame;
        color::COLOR_SCHEME_TYPE color_scheme;
        bool focus;

        Object()
        : frame()
        , color_scheme() 
        , focus(false) {}

        Object(const geometry::Rectangle& frame, const color::COLOR_SCHEME_TYPE& color_scheme)
        : frame(frame)
        , color_scheme(color_scheme) 
        , focus(false) {}

      public:
        virtual void show(bool show_flag) = 0;
        virtual void show_frame(bool show_flag) = 0;

        // Frame/Geometry getters
        virtual const int get_x() const { return this->frame.x; }
        virtual const int get_y() const { return this->frame.y; }
        virtual const unsigned int get_width() const { return this->frame.width; }
        virtual const unsigned int get_height() const { return this->frame.height; }
        virtual const geometry::Rectangle get_frame() const { return this->frame; }
        virtual bool hovered_by_mouse(const int& x, const int& y) const { return this->frame.has_point({x,y}); }

        // Colors setters/getters
        virtual void set_color_scheme(const color::COLOR_SCHEME_TYPE& color_scheme) { this->color_scheme = color_scheme; }
        virtual void update_color_scheme(const color::ColorSchemeID& key, const color::Color& value) { this->color_scheme[key] = value; }
        virtual const color::COLOR_SCHEME_TYPE& get_color_scheme() { return this->color_scheme; }

        // Frame manipulations
        virtual void move(const int& x, const int& y) {
          this->frame.move(x,y);
        }
        virtual void set_position(const int& x, const int& y) {
          this->frame.set_position(x,y);
        }
        virtual void set_center(geometry::Point&& p) {
          this->set_center(p.x,p.y);
        }
        virtual void set_center(const int& x, const int& y) {
          this->frame.set_center(x,y);
        }
        virtual void set_width(const unsigned int& width) { this->frame.width = width; }
        virtual void set_height(const unsigned int& height) { this->frame.height = height; }

        // Focus setters/getters
        virtual void set_focused(bool focus) { this->focus = focus; }
        virtual bool focused() const { return this->focus; }

        virtual ~Object() {};
    };

  }
}
#endif /* SRC_INCLUDE_INTERFACES_OBJECT_HPP */
