#ifndef SRC_INCLUDE_ABSTRACTIONS_OBSERVABLEVALUE_HPP
#define SRC_INCLUDE_ABSTRACTIONS_OBSERVABLEVALUE_HPP

#include <memory>
#include <list>
#include <functional>
#include <iostream>

namespace abstractions {
  class ObservableValueContainerWrapper {
    public:
      virtual ~ObservableValueContainerWrapper() {}
  };

  template <typename ValueType> class ObservableValue;

  template <typename ValueType>
  class ObservableValueUser {
    protected:
      std::shared_ptr<ObservableValue<ValueType>> observable_value;
      std::function<void()> value_changed_callback;

    public:
      ObservableValueUser<ValueType>(std::shared_ptr<ObservableValue<ValueType>> value, 
                                     std::function<void()> value_changed_callback = [](){}) 
      : observable_value(value) 
      , value_changed_callback(value_changed_callback) { 
        value->add_listening_user(this);
      }

      void value_changed() {
        value_changed_callback();
      }

      void change_value(const ValueType& new_value) {
        if(observable_value) {
          observable_value->change_value(new_value);
        }
      }
  };

  template <typename ValueType>
  class ObservableValue : public ObservableValueContainerWrapper {
    protected:
      ValueType value;
      std::list<ObservableValueUser<ValueType>* > users;

    public:
      ObservableValue<ValueType>(const ValueType& value) 
      : value(value) {
      }

      void add_listening_user(ObservableValueUser<ValueType>* user) {
        users.push_back(user);
      }

      void change_value(const ValueType& new_value) {
        this->value = new_value;
        for(auto& user : users) {
          if(user) {
            user->value_changed();
          }
        }
      }

      const ValueType get_value() const {
        return this->value;
      }
  };
}
#endif /* SRC_INCLUDE_ABSTRACTIONS_OBSERVABLEVALUE_HPP */
