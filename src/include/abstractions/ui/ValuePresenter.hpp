#ifndef SRC_INCLUDE_ABSTRACTIONS_UI_VALUEPRESENTER_HPP
#define SRC_INCLUDE_ABSTRACTIONS_UI_VALUEPRESENTER_HPP

#include "Object.hpp"
#include <memory>
#include <functional>
#include <any>
#include "Settings.hpp"

namespace abstractions::ui {

  struct ValuePresenter {
    virtual std::function<void()> bind_increase_value_trigger() = 0;
    virtual std::function<void()> bind_decrease_value_trigger() = 0;
    virtual ~ValuePresenter() {}

    protected:
      virtual void update_presenter() = 0;
  };

  template <typename ValueType, typename ValuePresentingObject>
    class ConfigValuePresenter : public Object, public ValuePresenter {
      protected:
        config_id config_value_id;
        std::unique_ptr<ValuePresentingObject> presenter;

      protected:
        ConfigValuePresenter<ValueType, ValuePresentingObject>(config_id config_value_id, 
            std::unique_ptr<ValuePresentingObject> presenter)
          : abstractions::ui::Object() 
            , config_value_id(config_value_id) 
            , presenter(std::move(presenter)) { }

        virtual ValueType& get_value() const {
          return config::get_concrete_ref<ValueType>(config_value_id);
        }

      public:
        virtual void increase_value() {
          ++config::get_concrete_ref<ValueType>(config_value_id);
          update_presenter();
        }

        virtual void decrease_value() {
          --config::get_concrete_ref<ValueType>(config_value_id);
          update_presenter();
        }

        virtual std::function<void()> bind_increase_value_trigger() override {
          return std::bind(&ConfigValuePresenter<ValueType, ValuePresentingObject>::increase_value, this);
        }

        virtual std::function<void()> bind_decrease_value_trigger() override {
          return std::bind(&ConfigValuePresenter<ValueType, ValuePresentingObject>::decrease_value, this);
        }

        virtual void show(bool show_flag) override {
          presenter->show(show_flag);
        }

        virtual void show_frame(bool show_flag) override {
          presenter->show_frame(show_flag);
        }

        // Frame/Geometry getters
        virtual const int get_x() const override { return presenter->get_x(); }
        virtual const int get_y() const override { return presenter->get_y(); }
        virtual const unsigned int get_width() const override { return presenter->get_frame().width; }
        virtual const unsigned int get_height() const override  { return presenter->get_frame().height; }
        virtual const geometry::Rectangle get_frame() const override { return presenter->get_frame(); }
        virtual bool hovered_by_mouse(const int& x, const int& y) const override { return presenter->get_frame().has_point({x,y}); }

        // Frame manipulations
        virtual void move(const int& x, const int& y) override {
          presenter->move(x,y);
        }
        virtual void set_position(const int& x, const int& y) override {
          presenter->set_position(x,y);
        }
        virtual void set_center(const int& x, const int& y) override {
          presenter->set_center(x,y);
        }
        virtual void set_width(const unsigned int& width) override { presenter->set_width(width); }
        virtual void set_height(const unsigned int& height) override { presenter->set_height(height); }

        // Focus setters/getters
        virtual void set_focused(bool focus) override { presenter->set_focused(focus); }
        virtual bool focused() const override { return presenter->focused(); }

        virtual ~ConfigValuePresenter<ValueType, ValuePresentingObject>() {}
    };
}

#endif /* SRC_INCLUDE_ABSTRACTIONS_UI_VALUEPRESENTER_HPP */
