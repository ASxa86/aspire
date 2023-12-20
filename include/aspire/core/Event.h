#pragma once

#include <aspire/export.hxx>
#include <chrono>

namespace aspire
{
	class ASPIRE_EXPORT Event
	{
	public:
		enum class Type : int
		{
			Unknown,
			Frame,
			Draw,
			Closed,
			MouseDoubleClicked,
			MousePressed,
			MouseReleased,
			MouseMoved,
			MouseScrolled,
			KeyPressed,
			KeyReleased
		};

		explicit Event(Type x);
		virtual ~Event() = default;

		auto getType() const -> Type;

	private:
		std::chrono::steady_clock::time_point timestamp{std::chrono::steady_clock::now()};
		Type type{Type::Unknown};
	};
}
