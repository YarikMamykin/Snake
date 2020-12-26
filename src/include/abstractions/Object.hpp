#ifndef SRC_INCLUDE_INTERFACES_OBJECT_HPP
#define SRC_INCLUDE_INTERFACES_OBJECT_HPP

#include "Rectangle.hpp"
#include <map>

namespace abstractions {
  namespace ui {
    typedef std::map<unsigned char, unsigned long> COLOR_SCHEME_TYPE;

    class Object {
      protected:
        // geometry::Rectangle prev_frame;
        geometry::Rectangle frame;
        COLOR_SCHEME_TYPE color_scheme;

        Object()
        : frame()
        , color_scheme() {}

        Object(const geometry::Rectangle& frame, const COLOR_SCHEME_TYPE& color_scheme)
        : frame(frame)
        , color_scheme(color_scheme) {}

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

        // Colors setters
        virtual void set_color_scheme(const COLOR_SCHEME_TYPE& color_scheme) { this->color_scheme = color_scheme; }
        virtual void update_color_scheme(const unsigned char& key, const unsigned long& value) { this->color_scheme[key] = value; }

        // Frame manipulations
        virtual void move(const int& x, const int& y) {
          this->frame.x += x;
          this->frame.y += y;
        }
        virtual void set_position(const int& x, const int& y) {
          this->frame.x = x;
          this->frame.y = y;
        }
        virtual void set_width(const unsigned int& width) { this->frame.width = width; }
        virtual void set_height(const unsigned int& height) { this->frame.height = height; }

        virtual ~Object() {};
    };

  }
}
#endif /* SRC_INCLUDE_INTERFACES_OBJECT_HPP */