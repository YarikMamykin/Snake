#pragma once
#include <gmock/gmock.h>
#include <events/event_handlers/ClientMessageHandler.hpp>
#include "AWindowMock.hpp"

struct WindowClientMessageHandlerMock : public AWindowMock, public events::ClientMessageHandler {
		MOCK_METHOD(void, handle_client_message, (const long* data), (override));
};

