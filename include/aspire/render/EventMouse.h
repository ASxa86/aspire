#pragma once

#include <cstdint>

namespace aspire::render
{
	struct EventMouse
	{
		enum class Type : int8_t
		{
			Unknown,
			Move,
			Press,
			Release
		};

		enum class Button : int8_t
		{
			Unknown,
			Left,
			Middle,
			Right
		};

		double x{};
		double y{};
		Type type{Type::Unknown};
		Button button{Button::Unknown};
	};
}