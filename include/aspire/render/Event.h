#pragma once

#include <aspire/render/EventMouse.h>
#include <aspire/render/EventWindow.h>
#include <variant>

namespace aspire::render
{
	using Event = std::variant<std::monostate, EventMouse, EventWindow>;
}