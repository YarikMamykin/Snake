#include <gmock/gmock.h>
#include <gtest/gtest.h>
#include <events/EventDispatcher/EventDispatcher.hpp>
#include <memory>
#include "mocks/WindowKeyPressHandlerMock.hpp"

namespace events::tests {
	TEST(EventsTest, KeyPressHandlerTest) {

		auto window_mock = std::make_shared<WindowKeyPressHandlerMock>();
		events::EventDispatcher dispatcher;

		XEvent event { .type = KeyPress };

		EXPECT_CALL(*window_mock, handle_key_press(NoSymbol, event.xkey.state)).Times(1);

		auto dispatch_event_call = dispatcher.dispatch_event(window_mock, event);
		dispatch_event_call();
	}

	TEST(EventsTest, KeyPressHandlerNoEventTest) {

		auto window_mock = std::make_shared<WindowKeyPressHandlerMock>();
		events::EventDispatcher dispatcher;

		XEvent event { .type = 0 };

		EXPECT_CALL(*window_mock, handle_key_press(NoSymbol, event.xkey.state)).Times(0);

		auto dispatch_event_call = dispatcher.dispatch_event(window_mock, event);
		EXPECT_THROW(dispatch_event_call(), std::bad_function_call);
	}
}
