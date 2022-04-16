#pragma once
#include <string>


namespace color {
  class Color;
}

namespace geometry {
  struct Rectangle;
  struct Point;
}

struct XWindowAttributes {
  unsigned int width, height;
};

namespace xlib {

  class XProxy {

    public:
      XProxy();
      ~XProxy();

      virtual void draw_rectangle(const geometry::Rectangle& r, const color::Color& color);
      virtual void fill_rectangle(const geometry::Rectangle& r, const color::Color& color);

      virtual void draw_circle(const geometry::Rectangle& r, const color::Color& color);
      virtual void fill_circle(const geometry::Rectangle& r, const color::Color& color);

      virtual void draw_text(const geometry::Point& p, const color::Color& color, const std::string& text);

      virtual XWindowAttributes get_window_attributes();
      virtual const unsigned int get_text_width(const std::string& text);
      virtual const unsigned int get_text_height();
  };
}
