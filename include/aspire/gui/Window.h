#pragma once

#include <aspire/core/Object.h>
#include <aspire/core/Pimpl.h>
#include <aspire/gui/Surface.h>
#include <array>

namespace aspire
{
	class ASPIRE_EXPORT Window : public Object
	{
	public:
		Window();
		~Window() override = default;

		auto setTitle(std::string_view x) -> void;
		auto getTitle() const noexcept -> std::string_view;

		auto setX(int x) noexcept -> void;
		auto getX() const noexcept -> int;

		auto setY(int x) noexcept -> void;
		auto getY() const noexcept -> int;

		auto setWidth(int x) noexcept -> void;
		auto getWidth() const noexcept -> int;

		auto setHeight(int x) noexcept -> void;
		auto getHeight() const noexcept -> int;

		auto setSurface(const Surface& x) -> void;
		auto getSurface() const -> const Surface&;

		auto onInitialized() -> void;

	protected:
		auto processEvents() -> void;

	private:
		std::string title{"aspire"};
		Surface surface{};
		std::array<int, 4> geometry{0, 0, 1280, 720};
		struct Impl;
		aspire::Pimpl<Impl> pimpl{};
	};
}
