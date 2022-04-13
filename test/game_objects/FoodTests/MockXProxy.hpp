#pragma once
#include <gmock/gmock.h>
#include "FakeXProxy.hpp"

namespace xlib {
	struct MockXProxy : public XProxy {
		MOCK_METHOD(void, fill_circle, (const geometry::Rectangle& r, const color::Color& c), (override));
	};
}
