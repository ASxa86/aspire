#pragma once

#include <aspire/gui/Surface.h>
#include <aspire/gui/export.hxx>

namespace aspire
{
	class ASPIRE_GUI_EXPORT Context
	{
	public:
		virtual ~Context() = default;

		virtual auto makeCurrent() -> void = 0;
		virtual auto makeRelease() -> void = 0;
		virtual auto create() -> void = 0;

		auto setSurface(const Surface& x) -> void;
		auto getSurface() const -> const Surface&;

	private:
		Surface surface;
	};
}
