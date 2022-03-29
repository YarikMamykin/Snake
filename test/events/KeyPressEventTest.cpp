#include <gmock/gmock.h>
#include <gtest/gtest.h>
#include <events/EventDispatcher.hpp>
#include "mocks/WindowKeyPressHandlerMock.hpp"

namespace events::tests {
	TEST(EventsTest, KeyPressHandlerTest) {

		WindowKeyPressHandlerMock window_mock;
		events::EventDispatcher dispatcher;

		XEvent event { .type = KeyPress };

		EXPECT_CALL(window_mock, handle_key_press(NoSymbol, event.xkey.state)).Times(1);

		auto dispatch_event_call = dispatcher.dispatch_event(&window_mock, event);
		dispatch_event_call();
	}

	TEST(EventsTest, KeyPressHandlerNoEventTest) {

		WindowKeyPressHandlerMock window_mock;
		events::EventDispatcher dispatcher;

		XEvent event { .type = 0 };

		EXPECT_CALL(window_mock, handle_key_press(NoSymbol, event.xkey.state)).Times(0);

		auto dispatch_event_call = dispatcher.dispatch_event(&window_mock, event);
		EXPECT_THROW(dispatch_event_call(), std::bad_function_call);
	}
}
