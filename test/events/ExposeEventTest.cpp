#include <gmock/gmock.h>
#include <gtest/gtest.h>
#include <events/EventDispatcher/EventDispatcher.hpp>
#include "mocks/WindowExposeEventHandlerMock.hpp"

namespace events::tests {
	TEST(EventsTest, ExposeEventHandlerTest) {

		auto window_mock = std::make_shared<WindowExposeEventHandlerMock>();
		events::EventDispatcher dispatcher;
		XEvent event { .type = Expose };

		EXPECT_CALL(*window_mock, handle_expose_event).Times(1);

		auto dispatch_event_call = dispatcher.dispatch_event(window_mock, event);
		dispatch_event_call();
	}

	TEST(EventsTest, ExposeEventHandlerNoEventTest) {

		auto window_mock = std::make_shared<WindowExposeEventHandlerMock>();
		events::EventDispatcher dispatcher;
		XEvent event { .type = 0 };

		EXPECT_CALL(*window_mock, handle_expose_event).Times(0);

		auto dispatch_event_call = dispatcher.dispatch_event(window_mock, event);
		EXPECT_THROW(dispatch_event_call(), std::bad_function_call);
	}

}
