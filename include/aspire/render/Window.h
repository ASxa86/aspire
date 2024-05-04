#pragma once

#include <aspire/core/Pimpl.h>
#include <aspire/render/export.hxx>
#include <string>

namespace aspire::render
{
	class ASPIRE_RENDER_EXPORT Window
	{
	public:
		Window();
		~Window();

		Window(const Window&) = delete;
		auto operator=(const Window&) = delete;

		Window(Window&&) noexcept = delete;
		auto operator=(Window&&) noexcept = delete;

		auto setTitle(std::string_view x) -> void;
		[[nodiscard]] auto getTitle() const -> std::string_view;

		auto setX(int x) noexcept -> void;
		[[nodiscard]] auto getX() const noexcept -> int;

		auto setY(int x) noexcept -> void;
		[[nodiscard]] auto getY() const noexcept -> int;

		auto setHeight(int x) noexcept -> void;
		[[nodiscard]] auto getHeight() const noexcept -> int;

		auto setWidth(int x) noexcept -> void;
		[[nodiscard]] auto getWidth() const noexcept -> int;

		auto create() -> void;
		auto destroy() -> void;
		auto valid() noexcept -> bool;
		auto frame() -> void;

	private:
		struct Impl;
		Pimpl<Impl> pimpl;
	};
}
