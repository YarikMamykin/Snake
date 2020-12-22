#ifndef SRC_INCLUDE_XLIB_X11_TEXTLABEL_HPP
#define SRC_INCLUDE_XLIB_X11_TEXTLABEL_HPP

#include "X11_Window.hpp"
#include "Rectangle.hpp"
#include <string>

namespace xlib {

  class ITextLabel {
    public:
      virtual void show() = 0;
      virtual void hide() = 0;
      virtual void show_frame() = 0;
      virtual void hide_frame() = 0;
      virtual void set_text(const std::string& text) = 0;
      virtual const std::string get_text() = 0;
      virtual void set_background_color(unsigned long color) = 0;
      virtual void set_frame_color(unsigned long color) = 0;
      virtual void set_text_color(unsigned long color) = 0;
      virtual void set_focused(bool focus) = 0;
      virtual bool focused() const = 0;
      virtual bool hovered_by_mouse(const int& x, const int& y) const = 0;
      virtual void set_frame(const int& x, const int& y, const unsigned int& width, const unsigned int& height) = 0;
      virtual const int get_x() const = 0;
      virtual const int get_y() const = 0;
      virtual const unsigned int get_width() const = 0;
      virtual const unsigned int get_height() const = 0;
      virtual void move(const int& x, const int& y) = 0;
      virtual void set_position(const int& x, const int& y) = 0;

      virtual ~ITextLabel() {};
  };

  class X11_TextLabel : public ITextLabel { 
    public:
      struct ColorScheme {
        unsigned long background;
        unsigned long frame;
        unsigned long text;

        ColorScheme() = default;
        ColorScheme(const ColorScheme&) = default;
      };

      static const unsigned int left_text_margin = 10U;
      static const unsigned int top_text_margin = 10U;
      static const unsigned int frame_weight = 3U;

    public:
      X11_TextLabel(X11_Window* parent_window);
      X11_TextLabel(const std::string& text, const geometry::Rectangle& frame, const ColorScheme& color_scheme, X11_Window* parent_window);
      ~X11_TextLabel();

      void show() override;
      void hide() override;
      void show_frame() override;
      void hide_frame() override;
      void set_text(const std::string& text) override;
      const std::string get_text() override;
      void set_background_color(unsigned long color) override;
      void set_frame_color(unsigned long color) override;
      void set_text_color(unsigned long color) override;
      void set_focused(bool focus) override;
      bool focused() const override;
      bool hovered_by_mouse(const int& x, const int& y) const override;
      void set_frame(const int& x, const int& y, const unsigned int& width, const unsigned int& height) override;
      const int get_x() const override;
      const int get_y() const override;
      const unsigned int get_width() const override;
      const unsigned int get_height() const override;
      void move(const int& x, const int& y) override;
      void set_position(const int& x, const int& y) override;

    private:
      void update();
      void update_frame();
      const unsigned int get_text_graphical_width() const;
      const unsigned int get_text_graphical_height() const;

    private:
      X11_Window* parent_window;
      ColorScheme color_scheme;
      geometry::Rectangle frame;
      std::string text;
      bool focus;
  };
}

#endif /* SRC_INCLUDE_XLIB_X11_TEXTLABEL_HPP */
