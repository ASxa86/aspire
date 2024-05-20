#pragma once

#include <aspire/core/Pimpl.h>
#include <aspire/core/Service.h>
#include <aspire/widget/Widget.h>
#include <aspire/widget/export.hxx>

namespace aspire::widget
{
	/// @brief This class defines an application window.
	class ASPIRE_WIDGET_EXPORT Window : public aspire::core::Service
	{
	public:
		Window();
		~Window() override;

		Window(const Window&) = delete;
		auto operator=(const Window&) = delete;

		Window(Window&&) noexcept = delete;
		auto operator=(Window&&) noexcept = delete;

		auto setX(int x) noexcept -> void;
		[[nodiscard]] auto getX() const noexcept -> int;

		auto setY(int x) noexcept -> void;
		[[nodiscard]] auto getY() const noexcept -> int;

		auto setHeight(int x) noexcept -> void;
		[[nodiscard]] auto getHeight() const noexcept -> int;

		auto setWidth(int x) noexcept -> void;
		[[nodiscard]] auto getWidth() const noexcept -> int;

		auto setTitle(std::string_view x) -> void;
		[[nodiscard]] auto getTitle() const -> std::string_view;

		auto setWidget(std::unique_ptr<Widget> x) -> void;
		[[nodiscard]] auto getWidget() const -> Widget*;

		auto event(aspire::core::Event* x) -> void override;

		auto frame() -> void override;

	protected:
		auto onStartup() -> void override;

	private:
		struct Impl;
		Pimpl<Impl> pimpl;
	};
}