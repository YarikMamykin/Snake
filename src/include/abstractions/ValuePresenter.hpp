#ifndef SRC_INCLUDE_ABSTRACTIONS_VALUEPRESENTER_HPP
#define SRC_INCLUDE_ABSTRACTIONS_VALUEPRESENTER_HPP

#include "Object.hpp"
#include <memory>
#include <functional>

namespace abstractions {
  namespace ui {

    template <typename ValueType, typename ValuePresentingObject = abstractions::ui::Object>
      class ValuePresenter : public Object {
        protected:
          ValueType value;
          std::unique_ptr<ValuePresentingObject> presenting_object;
          std::function<void()> increase_binder;
          std::function<void()> decrease_binder;

        protected:
          ValuePresenter<ValueType, ValuePresentingObject>(const ValueType& value, std::unique_ptr<ValuePresentingObject> presenting_object) 
            : abstractions::ui::Object() 
            , value(value) 
            , presenting_object(std::move(presenting_object)) { }

          virtual void update_presenter() = 0;

        public:
          virtual void increase_value() {
            ++value;
            update_presenter();
          }

          virtual void decrease_value() {
            --value;
            update_presenter();
          }

          virtual std::function<void()> bind_increase_value_trigger() {
            return std::bind(&ValuePresenter<ValueType, ValuePresentingObject>::increase_value, this);
          }

          virtual std::function<void()> bind_decrease_value_trigger() {
            return std::bind(&ValuePresenter<ValueType, ValuePresentingObject>::decrease_value, this);
          }

          virtual void show(bool show_flag) override {
            presenting_object->show(show_flag);
          }

          virtual void show_frame(bool show_flag) override {
            presenting_object->show_frame(show_flag);
          }

          // Frame/Geometry getters
          virtual const int get_x() const override { return presenting_object->get_x(); }
          virtual const int get_y() const override { return presenting_object->get_y(); }
          virtual const unsigned int get_width() const override { return presenting_object->get_frame().width; }
          virtual const unsigned int get_height() const override  { return presenting_object->get_frame().height; }
          virtual const geometry::Rectangle get_frame() const override { return presenting_object->get_frame(); }
          virtual bool hovered_by_mouse(const int& x, const int& y) const override { return presenting_object->get_frame().has_point({x,y}); }

          // Frame manipulations
          virtual void move(const int& x, const int& y) override {
            presenting_object->move(x,y);
          }
          virtual void set_position(const int& x, const int& y) override {
            presenting_object->set_position(x,y);
          }
          virtual void set_center(const int& x, const int& y) override {
            presenting_object->set_center(x,y);
          }
          virtual void set_width(const unsigned int& width) override { presenting_object->set_width(width); }
          virtual void set_height(const unsigned int& height) override { presenting_object->set_height(height); }

          // Focus setters/getters
          virtual void set_focused(bool focus) override { presenting_object->set_focused(focus); }
          virtual bool focused() const override { return presenting_object->focused(); }

          virtual ~ValuePresenter<ValueType, ValuePresentingObject>() {}
      };
  }
}
#endif /* SRC_INCLUDE_ABSTRACTIONS_VALUEPRESENTER_HPP */
