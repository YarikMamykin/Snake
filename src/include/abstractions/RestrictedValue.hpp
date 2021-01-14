#ifndef SRC_INCLUDE_ABSTRACTIONS_RESTRICTEDVALUE_HPP
#define SRC_INCLUDE_ABSTRACTIONS_RESTRICTEDVALUE_HPP

#include <stdexcept> 
#include <sstream>

namespace abstractions {
  template <typename ValueType>
    class RestrictedValue {
      protected:
        ValueType min_bound;
        ValueType value;
        ValueType max_bound;

      public:
        RestrictedValue<ValueType>() = delete;
        RestrictedValue<ValueType>(const RestrictedValue<ValueType>&) = default; 
        RestrictedValue<ValueType>(const ValueType& value, const ValueType& min, const ValueType& max) : min_bound(min), value(value), max_bound(max) { }

        const ValueType get_restricted_value() const { 
          if(!value_in_bounds()) {
            std::stringstream error_stream;
            error_stream << "Value " << value << " is out of bounds <" << min_bound << "..." << max_bound << ">";
            throw std::out_of_range(error_stream.str());
          }
          return value; 
        }

        const ValueType get_min() const {
          return min_bound;
        }

        const ValueType get_max() const {
          return max_bound;
        }

        bool value_in_bounds() const {
          return (min_bound <= value && value <= max_bound); 
        }

        void set_value(const ValueType& new_value) {
          if(min_bound <= new_value && new_value <= max_bound) {
            value = new_value;
          }
        }
        
        RestrictedValue<ValueType>& operator ++() {
          auto new_value = this->value;
          this->set_value(++new_value);
          return *this;
        }

        RestrictedValue<ValueType>& operator --() {
          auto new_value = this->value;
          this->set_value(--new_value);
          return *this;
        }
    };
}

namespace configuration {
  typedef abstractions::RestrictedValue<unsigned long> SNAKE_SPEED_TYPE;
}

#endif /* SRC_INCLUDE_ABSTRACTIONS_RESTRICTEDVALUE_HPP */
