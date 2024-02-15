#pragma once

#include <aspire/core/Event.h>
#include <aspire/math/Point.h>
#include <aspire/gui/export.hxx>

namespace aspire
{
	class ASPIRE_GUI_EXPORT EventMouse : public Event
	{
	public:
		enum class Button : int
		{
			Left,
			Middle,
			Right
		};

		explicit EventMouse(Type x);

		auto setPosition(const Point& x) noexcept -> void;
		auto getPosition() const noexcept -> const Point&;

		auto setButton(Button x) noexcept -> void;
		auto getButton() const noexcept -> Button;

	private:
		Point position{};
		Button button{};
	};
}
