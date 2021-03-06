#ifndef SRC_INCLUDE_XLIB_XLIBWRAPPER_HPP
#define SRC_INCLUDE_XLIB_XLIBWRAPPER_HPP
#include "xlib/XHeaders.hpp"
#include "geometry/Rectangle.hpp"
#include "color/Color.hpp"
#include <string>
#include <memory>

namespace xlib {
  struct XlibWrapper {
    public:
      Display* display;
      GC graphical_context;
      Window window;
      color::COLOR_SCHEME_TYPE window_color_scheme;
      XFontStruct* font_info;

    public:
      bool open_display();
      void close_display();

      bool load_font(const char* font_name);
      void free_font();

      bool create_graphical_context();
      bool create_window(geometry::Rectangle&& window_frame, 
                         color::COLOR_SCHEME_TYPE&& color_scheme, 
                         const unsigned int& border_width,
                         const char* name,
                         const char* font_name);
      XWindowAttributes get_window_attributes();
      void flush_buffer();
      void redraw_window_background();
      void destroy_window();

      void draw_rectangle(const geometry::Rectangle& r, const color::Color& color);
      void fill_rectangle(const geometry::Rectangle& r, const color::Color& color);

      void draw_circle(const geometry::Rectangle& r, const color::Color& color);
      void fill_circle(const geometry::Rectangle& r, const color::Color& color);

      void draw_text(const geometry::Point& p, const color::Color& color, const std::string& text);
      const unsigned int get_text_width(const std::string& text);
      const unsigned int get_text_height();

      void select_events_to_process();
      void next_event(XEvent* event);
      void send_event(long event_mask, XEvent* event);
      bool event_in_queue(int event_type, XEvent* event);

      const color::COLOR_SCHEME_TYPE& get_window_colorscheme() const;

      static std::shared_ptr<XlibWrapper> self();
  };
}


#endif /* SRC_INCLUDE_XLIB_XLIBWRAPPER_HPP */
