#pragma once

#include <chrono>
#include <variant>

namespace aspire
{
	struct EventWindow
	{
		enum class Type : int
		{
			None,
			Shown,
			Hidden,
			Exposed,
			Moved,
			Resized,
			Minimized,
			Maximized,
			Restored,
			Enter,
			Leave,
			FocusGained,
			FocusLost,
			Close
		};

		std::chrono::steady_clock::duration timestamp{};
		int x{};
		int y{};
		int width{};
		int height{};
		Type type{Type::None};
	};

	using Event = std::variant<std::monostate, EventWindow>;
}
