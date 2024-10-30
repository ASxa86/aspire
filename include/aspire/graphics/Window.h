#pragma once

#include <aspire/core/Pimpl.h>
#include <aspire/core/EnumMask.h>
#include <aspire/graphics/Color.h>
#include <aspire/graphics/Event.h>
#include <aspire/graphics/Vertex.h>
#include <aspire/graphics/export.hxx>
#include <functional>

namespace aspire
{
	class ASPIRE_GRAPHICS_EXPORT Window
	{
	public:
		enum class Hints : uint32_t
		{
			FullScreen = 0x00000001,
			OpenGL = 0x00000002,
			Shown = 0x00000004,
			Hidden = 0x00000008,
			Borderless = 0x00000010,
			Resizeable = 0x00000020,
			Minimized = 0x00000040,
			Maximized = 0x00000080,
			FullscreenDesktop = (static_cast<int>(FullScreen) | 0x00001000),
			Vulkan = 0x10000000,
			Metal = 0x20000000
		};

		Window(int width, int height, aspire::core::EnumMask<Hints> hints = {});
		~Window();

		auto open() const noexcept -> bool;
		auto close() noexcept -> void;
		auto processEvents() const noexcept -> void;
		auto clear(Color x = Color::Black) noexcept -> void;
		// auto draw(const Drawable& x) noexcept -> void;
		auto draw(const std::vector<Vertex>& x) -> void;
		auto display() noexcept -> void;

		auto onEvent(std::function<void(EventWindow)> x) noexcept -> void;

	private:
		struct Impl;
		Pimpl<Impl> pimpl;
	};
}
