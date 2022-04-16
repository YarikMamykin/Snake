#pragma once
#include <gmock/gmock.h>
#include <abstractions/ui/Window.hpp>

struct AWindowMock : public abstractions::ui::AWindow {
		MOCK_METHOD(void, show, (bool), (override));
		MOCK_METHOD(void, show_frame, (bool), (override));
		MOCK_METHOD(bool, closing, (), (const, noexcept, override));
		MOCK_METHOD(void, set_width, (const unsigned int&), (override));
		MOCK_METHOD(void, set_height, (const unsigned int&), (override));
};
