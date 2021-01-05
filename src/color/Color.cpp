#include "Color.hpp"

namespace color {
  Color::Color(const unsigned long& value) 
      : red(value >> 16)
        , green(value >> 8)
        , blue(value) {}

    Color::Color(const std::string& value) 
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

    const unsigned long Color::to_long() const { 
      unsigned long result = red; 
      result = result << 8;
      result |= green;
      result = result << 8;
      result |= blue;
      return result;
    }

    const std::string Color::to_string() const { 
      std::string result;
      for(auto& color_part : {red, green, blue}) {
        result += std::to_string(color_part) + " ";
      }
      return result;
    }

    bool Color::operator == (const Color& a) const {
      return (a.red == red) &&
        (a.green == green) &&
        (a.blue == blue);
    }
}
