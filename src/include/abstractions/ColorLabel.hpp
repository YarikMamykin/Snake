#ifndef SRC_INCLUDE_ABSTRACTIONS_COLORLABEL_HPP
#define SRC_INCLUDE_ABSTRACTIONS_COLORLABEL_HPP

#include "Object.hpp"
#include <sstream>
#include <list>
#include <iostream>

namespace abstractions {
  namespace ui {

    class ColorLabel : public Object {
      public:
        struct Color {
            unsigned char red, green, blue;

            Color() = default;
            Color(const unsigned long& value) 
            : red(value >> 16)
            , green(value >> 8)
            , blue(value) {}

            Color(const std::string& value) 
            : red(0u)
            , green(0u)
            , blue(0u) {
              const bool value_contains_hash_char = (value.find_first_of('#') == 0u);
              const bool value_length_is_enough = (value.size() == 7u);
              if(!value_contains_hash_char || !value_length_is_enough) {
                return;
              }

              unsigned short buffer;
              std::stringstream(value.substr(1u, 2)) >> std::hex >> buffer; red = buffer;
              std::stringstream(value.substr(3u, 2)) >> std::hex >> buffer; green = buffer;
              std::stringstream(value.substr(5u, 2)) >> std::hex >> buffer; blue = buffer;
            }

            const unsigned long to_long() const { 
              unsigned long result = red; 
              result = result << 8;
              result |= green;
              result = result << 8;
              result |= blue;
              return result;
            }

            const std::string to_string() const { 
              std::string result;
              for(auto& color_part : {red, green, blue}) {
                result += std::to_string(color_part) + " ";
              }
              return result;
            }

            bool operator == (const Color& a) const {
              return (a.red == red) &&
                     (a.green == green) &&
                     (a.blue == blue);
            }
        };

        struct ColorPallete {
          ColorPallete() 
          : colors({ Color("#ff0000"), Color("#00ff00"), Color("#0000ff") }) 
          , current_color(colors.begin()) { }

          ColorPallete(const Color& color)
          : ColorPallete() {
            set_current_color(color);
          }

          ColorPallete(const ColorPallete& color_pallete) 
          : colors(color_pallete.colors) 
          , current_color(colors.begin()) {
            set_current_color(color_pallete.get_current_color());
          }

          ColorPallete& operator ++() {
            if(current_color == std::prev(colors.end()) || current_color == colors.end()) {
              current_color = colors.begin();
            } else {
              current_color = std::next(current_color);
            }
            return *this;
          }

          ColorPallete& operator --() {
            if(current_color == colors.begin()) {
              current_color = std::prev(colors.end());
            } else { 
              current_color = std::prev(current_color);
            }
            return *this;
          }

          const Color& get_current_color() const {
            return *current_color;
          }

          void set_current_color(const Color& color) {
            current_color = std::find(colors.begin(), colors.end(), color);
            if(current_color == colors.end()) {
              colors.push_front(color);
              current_color = colors.begin();
            }
          }

          private:
            std::list<Color> colors;
            std::list<Color>::iterator current_color;
        } color_pallete;

        ColorLabel() : Object() {}
        ColorLabel(const Color& color,
                   const geometry::Rectangle& frame, 
                   const abstractions::ui::COLOR_SCHEME_TYPE& color_scheme) 
        : Object(frame, color_scheme) 
        , color_pallete(color) {}

      public:
        virtual void set_color(const Color& color) { this->color_pallete.set_current_color(color); }
        virtual void set_color_pallete(const ColorPallete& color_pallete) { this->color_pallete = color_pallete; }
        virtual const Color get_color() const { return this->color_pallete.get_current_color(); }

        virtual ~ColorLabel() {};
    };
  }
}

#endif /* SRC_INCLUDE_ABSTRACTIONS_COLORLABEL_HPP */
