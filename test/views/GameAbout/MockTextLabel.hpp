#pragma once
#include <gmock/gmock.h>
#include <abstractions/ui/TextLabel.hpp>

struct MockTextLabel  : public abstractions::ui::TextLabel { 
      MOCK_METHOD(void, show, (bool), (override));
      MOCK_METHOD(void, show_frame, (bool), (override));
      MOCK_METHOD(void, set_center, (geometry::Point&&), (override));
};
