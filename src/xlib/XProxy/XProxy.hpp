#pragma once

#include <xlib/XHandlers.hpp>
#include <xlib/XSettings.hpp>
#include <xlib/XError.hpp>
#include <geometry/Rectangle.hpp>
#include <color/Color.hpp>
#include <string>
#include <memory>
#include <variant>
#include <utility>

namespace xlib {
  class XProxy {

      XHandlers m_handlers;
      XSettings m_settings;

      XProxy(std::unique_ptr<XSettings> settings, XError& err);

      XError init_X_system(std::unique_ptr<XSettings> settings);
      XError deinit_X_system();

    public:

      static std::variant<std::reference_wrapper<XProxy>, XError> 
        create(std::unique_ptr<XSettings> settings) noexcept;

      ~XProxy();

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

      void next_event(XEvent* event);
      void send_event(long event_mask, XEvent* event);
      void send_client_event(long event_mask, XEvent* event);
      bool event_in_queue(int event_type, XEvent* event);
  };
}
