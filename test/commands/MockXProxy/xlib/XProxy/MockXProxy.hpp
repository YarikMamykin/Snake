#pragma once

#include <gtest/gtest.h>
#include <gmock/gmock.h>
#include "XProxy.hpp"

namespace xlib {
	struct MockXProxy : public XProxy {
      MOCK_METHOD(void, draw_rectangle, (const geometry::Rectangle& r, const color::Color& color), (override));
      MOCK_METHOD(void, fill_rectangle, (const geometry::Rectangle& r, const color::Color& color), (override));

      MOCK_METHOD(void, draw_circle, (const geometry::Rectangle& r, const color::Color& color), (override));
      MOCK_METHOD(void, fill_circle, (const geometry::Rectangle& r, const color::Color& color), (override));

      MOCK_METHOD(void, draw_text, (const geometry::Point& p, const color::Color& color, const std::string& text), (override));
	};
}
