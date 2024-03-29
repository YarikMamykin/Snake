#pragma once
#include <gmock/gmock.h>
#include <events/event_handlers/MouseButtonPressHandler.hpp>
#include "AWindowMock.hpp"

struct WindowMouseButtonPressHandlerMock : public AWindowMock, public events::MouseButtonPressHandler {
		MOCK_METHOD(void, handle_button_press, (const int& x, const int& y, const unsigned int& button), (override));
};

