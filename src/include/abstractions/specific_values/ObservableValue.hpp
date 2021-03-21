#ifndef SRC_INCLUDE_ABSTRACTIONS_OBSERVABLEVALUE_HPP
#define SRC_INCLUDE_ABSTRACTIONS_OBSERVABLEVALUE_HPP

#include <memory>
#include <list>
#include <functional>

namespace abstractions {
  template <typename ValueType> class ObservableValue;

  class ObservableValueContainerWrapper {
    public:
      template<typename ValueType> static 
        std::shared_ptr<ObservableValue<ValueType>> to_concrete_value(std::shared_ptr<ObservableValueContainerWrapper> value) {
          return std::static_pointer_cast<ObservableValue<ValueType>>(value);
        }

      virtual ~ObservableValueContainerWrapper() {}
  };

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
        observable_value->add_listening_user(this);
      }

      void value_changed() {
        value_changed_callback();
      }

      void change_value(const ValueType& new_value) {
        if(observable_value) {
          observable_value->change_value(new_value);
        }
      }

      virtual ~ObservableValueUser<ValueType>() {
        observable_value->delete_listening_user(this);
      }
  };

  template <typename ValueType>
  class ObservableValue final : public ObservableValueContainerWrapper {
    protected:
      ValueType value;
      std::list<ObservableValueUser<ValueType>* > users;

    public:
      ObservableValue<ValueType>(const ValueType& value)
      : value(value) {
      }

      ObservableValue<ValueType>(ValueType&& value)
      : value(value) {
      }

      template <typename... Args>
      ObservableValue<ValueType>(Args... args) 
      : ObservableValue<ValueType>(ValueType(args...)) {
      }

      void add_listening_user(ObservableValueUser<ValueType>* user) {
        users.push_back(user);
      }

      void delete_listening_user(ObservableValueUser<ValueType>* user) {
        users.remove(user);
      }

      void notify_users() const {
        for(auto& user : users) {
          if(user) {
            user->value_changed();
          }
        }
      }

      void change_value(const ValueType& new_value) {
        this->value = new_value;
        notify_users();
      }

      void increase() {
        ++this->value;
        notify_users();
      }

      void decrease() {
        --this->value;
        notify_users();
      }

      const ValueType get_value() const {
        return this->value;
      }

      std::shared_ptr<ObservableValueContainerWrapper> wrap() {
        return std::shared_ptr<ObservableValueContainerWrapper>(static_cast<ObservableValueContainerWrapper*>(this));
      }
  };
}
#endif /* SRC_INCLUDE_ABSTRACTIONS_OBSERVABLEVALUE_HPP */
