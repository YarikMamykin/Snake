#pragma once
#include <gmock/gmock.h>
#include <abstractions/event_handling/KeyPressHandler.hpp>
#include "AWindowMock.hpp"

struct WindowKeyPressHandlerMock : public AWindowMock, public events::KeyPressHandler {
		MOCK_METHOD(void, handle_key_press, (const KeySym& key_sym, const unsigned int& mask), (override));
};

KeySym XLookupKeysym(XKeyEvent*, int) {
	return {};
}

