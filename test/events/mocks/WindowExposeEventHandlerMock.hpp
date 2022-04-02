#pragma once
#include <gmock/gmock.h>
#include <events/event_handlers/ExposeEventHandler.hpp>
#include "AWindowMock.hpp"

struct WindowExposeEventHandlerMock : public AWindowMock, public events::ExposeEventHandler {
		MOCK_METHOD(void, handle_expose_event, (), (override));
};

