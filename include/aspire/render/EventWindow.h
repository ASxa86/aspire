#pragma once

#include <cstdint>

namespace aspire::render
{
	struct EventWindow
	{
		enum class Type : int
		{
			Unknown,
			Close,
			Show,
			Hide,
			Resize
		};

		int width{};
		int height{};
		Type type{Type::Unknown};
	};
}