#pragma once
#include <gmock/gmock.h>
#include <events/event_handlers/MouseMotionHandler.hpp>
#include "AWindowMock.hpp"

struct WindowMouseMotionHandlerMock : public AWindowMock, public events::MouseMotionHandler {
		MOCK_METHOD(void, handle_mouse_motion, (const int& x, const int& y), (override));
};

