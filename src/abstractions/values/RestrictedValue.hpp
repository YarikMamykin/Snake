#pragma once
#include <algorithm>

namespace abstractions::values {
  template <typename ValueType>
    class RestrictedValue {
      protected:
        ValueType min_bound;
        ValueType value;
        ValueType max_bound;
        const unsigned int iteration_step;

      public:
        RestrictedValue<ValueType>() = delete;
        RestrictedValue<ValueType>(const RestrictedValue<ValueType>&) = default; 
        constexpr RestrictedValue<ValueType>(const ValueType& value, 
                                   const ValueType& min, 
                                   const ValueType& max, 
                                   unsigned int&& iteration_step = 1u) 
        : min_bound(min)
        , value(std::clamp(value, min, max))
        , max_bound(max)
        , iteration_step(iteration_step) { }

        const ValueType get_restricted_value() const noexcept { return value; }
        const ValueType get_min() const noexcept { return min_bound; }
        const ValueType get_max() const noexcept { return max_bound; }

        void set_value(const ValueType& new_value) noexcept { 
          value = std::clamp(new_value, min_bound, max_bound); 
        }
        
        RestrictedValue<ValueType>& operator ++() {
          auto new_value = this->value;
          for(unsigned int i = 0; i < iteration_step; ++i) {
            ++new_value;
          }
          this->set_value(new_value);
          return *this;
        }

        RestrictedValue<ValueType>& operator --() {
          auto new_value = this->value;
          for(unsigned int i = iteration_step; i > 0; --i) {
            --new_value;
          }
          this->set_value(new_value);
          return *this;
        }
    };

  template <typename ValueType> 
    RestrictedValue(
        const ValueType& value,
        const ValueType& min,
        const ValueType& max,
        unsigned int&& iteration_step = 1u) -> RestrictedValue<ValueType>;
}

