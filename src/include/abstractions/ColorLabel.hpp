#ifndef SRC_INCLUDE_ABSTRACTIONS_COLORLABEL_HPP
#define SRC_INCLUDE_ABSTRACTIONS_COLORLABEL_HPP

#include "Object.hpp"
#include <sstream>

namespace abstractions {
  namespace ui {

    class ColorLabel : public Object {
      public:
        struct Color {
            unsigned char red, green, blue;

            Color() = default;
            Color(const unsigned long& value) : red(value >> 16), green(value >> 8), blue(value) {}
            Color(const std::string& value) {
              const bool value_contains_hash_char = (value.find_first_of('#') != 0u);
              const bool value_length_is_enough = (value.size() != 7u);
              if(!value_contains_hash_char || !value_length_is_enough) {
                return;
              }

              std::stringstream(value.substr(1u, 2)) >> std::hex >> red;
              std::stringstream(value.substr(3u, 2)) >> std::hex >> green;
              std::stringstream(value.substr(5u, 2)) >> std::hex >> blue;
            }

            const unsigned long to_long() const { 
              unsigned long result = red; 
              result = result << 8;
              result |= green;
              result = result << 8;
              result |= blue;
              return result;
            }

            Color& operator++() {
              ++red;
              ++green;
              ++blue;

              return *this;
            }

            Color& operator--() {
              --red;
              --green;
              --blue;

              return *this;
            }

        } color;

        ColorLabel() : Object() {}
        ColorLabel(const Color& color,
                   const geometry::Rectangle& frame, 
                   const abstractions::ui::COLOR_SCHEME_TYPE& color_scheme) 
        : Object(frame, color_scheme) 
        , color(color) {}

      public:
        virtual void set_color(const Color& color) { this->color = color; }
        virtual const Color get_color() const { return this->color; }

        virtual ~ColorLabel() {};
    };
  }
}

#endif /* SRC_INCLUDE_ABSTRACTIONS_COLORLABEL_HPP */
