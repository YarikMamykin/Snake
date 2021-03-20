#ifndef SRC_INCLUDE_ABSTRACTIONS_OBSERVABLEVALUEPRESENTER_HPP
#define SRC_INCLUDE_ABSTRACTIONS_OBSERVABLEVALUEPRESENTER_HPP

#include <memory>
#include "ObservableValue.hpp"
#include "ValuePresenter.hpp"

namespace abstractions::ui {

  template <typename ValueType, typename ValuePresentingObject = abstractions::ui::Object>
    class ObservableValuePresenter : public ValuePresenter<ValueType, ValuePresentingObject>, 
    public ObservableValueUser<ValueType> {
      protected:
        ObservableValuePresenter<ValueType, ValuePresentingObject>(std::shared_ptr<ObservableValue<ValueType>> value, 
            std::unique_ptr<ValuePresentingObject> presenting_object)
          : abstractions::ui::ValuePresenter<ValueType, ValuePresentingObject>(value->get_value(), std::move(presenting_object))
            , abstractions::ObservableValueUser<ValueType>(value) { }

      public:
        virtual void increase_value() override {
          this->observable_value->increase();
          this->update_presenter();
        }

        virtual void decrease_value() override {
          this->observable_value->decrease();
          this->update_presenter();
        }

        virtual std::function<void()> bind_increase_value_trigger() override {
          return std::bind(&ObservableValuePresenter<ValueType, ValuePresentingObject>::increase_value, this);
        }

        virtual std::function<void()> bind_decrease_value_trigger() override {
          return std::bind(&ObservableValuePresenter<ValueType, ValuePresentingObject>::decrease_value, this);
        }

        virtual std::shared_ptr<ObservableValue<ValueType>> get_observable_value() const { return this->observable_value; }

        virtual ~ObservableValuePresenter<ValueType, ValuePresentingObject>() {}

      private:
        using ValuePresenter<ValueType, ValuePresentingObject>::get_value; // disable parent get_value
    };
}

#endif /* SRC_INCLUDE_ABSTRACTIONS_OBSERVABLEVALUEPRESENTER_HPP */
