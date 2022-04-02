#include <gmock/gmock.h>
#include <gtest/gtest.h>
#include <events/EventDispatcher/EventDispatcher.hpp>
#include "mocks/WindowMouseMotionHandlerMock.hpp"

namespace events::tests {

	TEST(EventsTest, MouseMotionHandlerTest) {

		WindowMouseMotionHandlerMock window_mock;
		events::EventDispatcher dispatcher;

		XEvent event { .type = MotionNotify };

		EXPECT_CALL(window_mock, handle_mouse_motion(event.xmotion.x, event.xmotion.y)).Times(1);

		auto dispatch_event_call = dispatcher.dispatch_event(&window_mock, event);
		dispatch_event_call();
	}

	TEST(EventsTest, MouseMotionHandlerNoEventTest) {

		WindowMouseMotionHandlerMock window_mock;
		events::EventDispatcher dispatcher;

		XEvent event { .type = 0 };

		EXPECT_CALL(window_mock, handle_mouse_motion(event.xmotion.x, event.xmotion.y)).Times(0);

		auto dispatch_event_call = dispatcher.dispatch_event(&window_mock, event);
		EXPECT_THROW(dispatch_event_call(), std::bad_function_call);
	}

}
