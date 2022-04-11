#include "Color.hpp"
#include <string>
#include <stdexcept>

namespace color {

  static_assert(sizeof(unsigned long) >= 3);

  Color::Color(unsigned long value) noexcept 
  : m_self(value) {}

  Color::Color(std::string_view value) {

    const bool value_contains_hash_char = (value.find_first_of('#') == 0u);
    const bool value_length_is_enough = (value.size() == 7u);

    if(!value_contains_hash_char || !value_length_is_enough) {
      throw std::runtime_error("Wrong hex color value provided!");
    }

    const auto r_byte_string = std::string(value.substr(1u, 2));
    const auto g_byte_string = std::string(value.substr(3u, 2));
    const auto b_byte_string = std::string(value.substr(5u, 2));   

    m_self = 
      (std::stoul(r_byte_string, nullptr, 16) << 16) |
      (std::stoul(g_byte_string, nullptr, 16) << 8) |
      (std::stoul(b_byte_string, nullptr, 16));
  }

  Color::operator unsigned long () const { 
    return m_self.to_ulong();
  }

  bool Color::operator == (const Color& a) const {
    return m_self == a.m_self;
  }

  unsigned char Color::red() const noexcept {
    const unsigned long v = m_self.to_ulong();
    const unsigned char* p = reinterpret_cast<const unsigned char*>(&v);
    return *(p + 2);
  }

  unsigned char Color::green() const noexcept {
    const unsigned long v = m_self.to_ulong();
    const unsigned char* p = reinterpret_cast<const unsigned char*>(&v);
    return *(p + 1);
  }

  unsigned char Color::blue() const noexcept {
    const unsigned long v = m_self.to_ulong();
    const unsigned char* p = reinterpret_cast<const unsigned char*>(&v);
    return *p;
  }
}
