/*
   Simple Xlib application for creating a window and drawing a box in it.
   gcc input.c -o output -lX11
   compile with !g++ --std=c++11 % -L/usr/X11/lib -lX11 -lstdc++
   */

#include "X11_Window.hpp"
#include "XlibWrapper.hpp"
#include "EventHandler.hpp"
#include "Settings.hpp"
#include <iostream>
#include <memory>

void LaunchApp() {
  using namespace xlib;
  using namespace events;
  using namespace configuration;
  XInitThreads();

  xlib::WindowSettings win_sets = {
    .frame = abstractions::ObservableValueContainerWrapper::to_concrete_value<geometry::Rectangle>(Settings::get(ConfigID::WINDOW_FRAME))->get_value(),
    .color_scheme = abstractions::ObservableValueContainerWrapper::to_concrete_value<color::COLOR_SCHEME_TYPE>(Settings::get(ConfigID::WINDOW_COLOR_SCHEME))->get_value(),
    .border_width = abstractions::ObservableValueContainerWrapper::to_concrete_value<unsigned int>(Settings::get(ConfigID::WINDOW_BORDER_WIDTH))->get_value(),
    .name = abstractions::ObservableValueContainerWrapper::to_concrete_value<std::string>(Settings::get(ConfigID::WINDOW_NAME))->get_value(),
    .font_name = abstractions::ObservableValueContainerWrapper::to_concrete_value<std::string>(Settings::get(ConfigID::WINDOW_FONT_NAME))->get_value()
  };

  std::shared_ptr<abstractions::ui::AWindow> x_window(new X11_Window(views::ViewID::MENU, win_sets));
  EventHandler ehandler(std::move(x_window));
  ehandler.event_handler_loop();
}

int main(void)
{
  LaunchApp();
  std::cout << "GOODBYE!" << std::endl;
  return 0;
}
