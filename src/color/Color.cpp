#include "color/Color.hpp"

namespace {
  const auto zero_byte = static_cast<std::byte>(0u);
  auto convert_to_byte = [](const auto& value) -> std::byte {
    return static_cast<std::byte>(value);
  };
  auto byte_to_ulong = [](const std::byte& byte) -> unsigned long {
    return static_cast<unsigned long>(byte);
  };
}

namespace color {
  Color::Color(const unsigned long& value) 
    : red(convert_to_byte(value >> 16))
    , green(convert_to_byte(value >> 8))
    , blue(convert_to_byte(value)) {}

    Color::Color(const char* value) : Color(std::string(value)) { }
    Color::Color(const std::string& value) 
      : red(zero_byte)
      , green(zero_byte)
      , blue(zero_byte) {
          const bool value_contains_hash_char = (value.find_first_of('#') == 0u);
          const bool value_length_is_enough = (value.size() == 7u);
          if(!value_contains_hash_char || !value_length_is_enough) {
            return;
          }

          unsigned short buffer;
          std::stringstream(value.substr(1u, 2)) >> std::hex >> buffer; red = convert_to_byte(buffer);
          std::stringstream(value.substr(3u, 2)) >> std::hex >> buffer; green = convert_to_byte(buffer);
          std::stringstream(value.substr(5u, 2)) >> std::hex >> buffer; blue = convert_to_byte(buffer);
        }

    Color::operator unsigned long () const { 
      unsigned long result = byte_to_ulong(red);
      result = result << 8;
      result |= byte_to_ulong(green);
      result = result << 8;
      result |= byte_to_ulong(blue);
      return result;
    }

    Color::operator std::string () const {
      std::stringstream result_stream;
      result_stream << "#" << std::hex << std::noshowbase << static_cast<unsigned long>(*this);
      return result_stream.str().insert(1u, 7u - result_stream.str().size(), '0');
    }

    bool Color::operator == (const Color& a) const {
      return (a.red   == this->red) &&
             (a.green == this->green) &&
             (a.blue  == this->blue);
    }
}
