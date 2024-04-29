#pragma once

#include <aspire/core/Pimpl.h>
#include <aspire/render/export.hxx>
#include <string>

namespace aspire::render
{
	class ASPIRE_RENDER_EXPORT Window
	{
	public:
		struct Traits
		{
			std::string title;
			int x{};
			int y{};
			int width{};
			int height{};
		};

		Window(const Traits& x);

		auto move(int x, int y) -> void;
		auto resize(int width, int height) -> void;
		auto frame() -> void;

	private:
		struct Impl;
		Pimpl<Impl> pimpl;
	};
}
