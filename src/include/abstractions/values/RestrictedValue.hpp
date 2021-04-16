#ifndef SRC_INCLUDE_ABSTRACTIONS_UI_RESTRICTEDVALUE_HPP
#define SRC_INCLUDE_ABSTRACTIONS_UI_RESTRICTEDVALUE_HPP

#include <stdexcept> 
#include <sstream>
#include <iostream>
#include <algorithm>

namespace abstractions {
  template <typename ValueType>
    class RestrictedValue {
      protected:
        ValueType min_bound;
        ValueType value;
        ValueType max_bound;
        const unsigned int step;

      public:
        RestrictedValue<ValueType>() = delete;
        RestrictedValue<ValueType>(const RestrictedValue<ValueType>&) = default; 
        RestrictedValue<ValueType>(const ValueType& value, const ValueType& min, const ValueType& max, const unsigned int& step = 1u) : min_bound(min), value(std::clamp(value, min, max)), max_bound(max), step(step) { }

        const ValueType get_restricted_value() const { return value; }
        const ValueType get_min() const { return min_bound; }
        const ValueType get_max() const { return max_bound; }
        void set_value(const ValueType& new_value) { value = std::clamp(new_value, min_bound, max_bound); }
        void set_min(const ValueType& min_value) { min_bound(min_value); } 
        void set_max(const ValueType& max_value) { max_bound(max_value); }
        
        RestrictedValue<ValueType>& operator ++() {
          auto new_value = this->value;
          for(unsigned int i = 0; i < step; ++i) {
            ++new_value;
          }
          this->set_value(new_value);
          return *this;
        }

        RestrictedValue<ValueType>& operator --() {
          auto new_value = this->value;
          for(unsigned int i = step; i > 0; --i) {
            --new_value;
          }
          this->set_value(new_value);
          return *this;
        }
    };
}

namespace configuration {
  typedef abstractions::RestrictedValue<unsigned long> RESTRICTED_ULONG;
  typedef abstractions::RestrictedValue<int> RESTRICTED_INT;
  typedef abstractions::RestrictedValue<unsigned int> RESTRICTED_UINT;
}


#endif /* SRC_INCLUDE_ABSTRACTIONS_UI_RESTRICTEDVALUE_HPP */
