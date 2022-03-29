#pragma once
#include <gmock/gmock.h>
#include <abstractions/event_handling/ExposeEventHandler.hpp>
#include "AWindowMock.hpp"

struct WindowExposeEventHandlerMock : public AWindowMock, public events::ExposeEventHandler {
		MOCK_METHOD(void, handle_expose_event, (), (override));
};

