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
			Hide
		};

		Type type{Type::Unknown};
	};
}