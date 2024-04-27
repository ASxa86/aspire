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
		auto setX(int x) noexcept -> void;
		[[nodiscard]] auto getX() const noexcept -> int;

		auto setY(int x) noexcept -> void;
		[[nodiscard]] auto getY() const noexcept -> int;

		auto setHeight(int x) noexcept -> void;
		[[nodiscard]] auto getHeight() const noexcept -> int;

		auto setWidth(int x) noexcept -> void;
		[[nodiscard]] auto getWidth() const noexcept -> int;

	private:
		struct Impl;
		Pimpl<Impl> pimpl;
	};
}