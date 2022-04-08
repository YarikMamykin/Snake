#include <gmock/gmock.h>
#include <gtest/gtest.h>
#include <events/EventDispatcher/EventDispatcher.hpp>
#include "mocks/WindowMouseButtonPressHandlerMock.hpp"

namespace events::tests {

	TEST(EventsTest, MouseButtonPressHandlerTest) {

		auto window_mock = std::make_shared<WindowMouseButtonPressHandlerMock>();
		events::EventDispatcher dispatcher;

		XEvent event { .type = ButtonPress };

		EXPECT_CALL(*window_mock, handle_button_press(event.xmotion.x, event.xmotion.y, event.xbutton.button)).Times(1);

		auto dispatch_event_call = dispatcher.dispatch_event(window_mock, event);
		dispatch_event_call();
	}


	TEST(EventsTest, MouseButtonPressHandlerNoEventTest) {

		auto window_mock = std::make_shared<WindowMouseButtonPressHandlerMock>();
		events::EventDispatcher dispatcher;

		XEvent event { .type = 0 };

		EXPECT_CALL(*window_mock, handle_button_press(event.xmotion.x, event.xmotion.y, event.xbutton.button)).Times(0);

		auto dispatch_event_call = dispatcher.dispatch_event(window_mock, event);
		EXPECT_THROW(dispatch_event_call(), std::bad_function_call);
	}

}
