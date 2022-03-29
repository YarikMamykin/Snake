#include <gmock/gmock.h>
#include <gtest/gtest.h>
#include <events/EventDispatcher.hpp>
#include "mocks/WindowClientMessageHandlerMock.hpp"

namespace events::tests {

	TEST(EventsTest, ClientMessageHandlerTest) {

		WindowClientMessageHandlerMock window_mock;
		events::EventDispatcher dispatcher;

		XEvent event { .type = ClientMessage };
		event.xclient.data.l[0] = 0l;
		event.xclient.data.l[1] = 1l;
		event.xclient.data.l[2] = 2l;
		event.xclient.data.l[3] = 3l;
		event.xclient.data.l[4] = 4l;

		EXPECT_CALL(window_mock, handle_client_message(event.xclient.data.l)).Times(1);

		auto dispatch_event_call = dispatcher.dispatch_event(&window_mock, event);
		dispatch_event_call();
	}


	TEST(EventsTest, ClientMessageHandlerNoEventTest) {

		WindowClientMessageHandlerMock window_mock;
		events::EventDispatcher dispatcher;

		XEvent event { .type = 0 };
		event.xclient.data.l[0] = 0l;
		event.xclient.data.l[1] = 1l;
		event.xclient.data.l[2] = 2l;
		event.xclient.data.l[3] = 3l;
		event.xclient.data.l[4] = 4l;

		EXPECT_CALL(window_mock, handle_client_message(event.xclient.data.l)).Times(0);

		auto dispatch_event_call = dispatcher.dispatch_event(&window_mock, event);
		EXPECT_THROW(dispatch_event_call(), std::bad_function_call);
	}

}
