#pragma once

#include <aspire/core/Object.h>
#include <aspire/core/Pimpl.h>
#include <aspire/widget/export.hxx>

namespace aspire::widget
{
	class ASPIRE_WIDGET_EXPORT Widget : public aspire::core::Object
	{
	public:
		Widget();
		~Widget() override;

		Widget(const Widget&) = delete;
		auto operator=(const Widget&) = delete;

		Widget(Widget&&) noexcept = delete;
		auto operator=(Widget&&) noexcept = delete;

		auto setX(int x) noexcept -> void;
		[[nodiscard]] auto getX() const noexcept -> int;

		auto setY(int x) noexcept -> void;
		[[nodiscard]] auto getY() const noexcept -> int;

		auto setHeight(int x) noexcept -> void;
		[[nodiscard]] auto getHeight() const noexcept -> int;

		auto setWidth(int x) noexcept -> void;
		[[nodiscard]] auto getWidth() const noexcept -> int;

		[[nodiscard]] auto childWidgets() const noexcept -> std::vector<Widget*>;

	private:
		struct Impl;
		Pimpl<Impl> pimpl;
	};
}