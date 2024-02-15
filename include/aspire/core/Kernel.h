#pragma once

#include <aspire/core/Object.h>

namespace aspire
{
	class ASPIRE_CORE_EXPORT Kernel : public Object
	{
	public:
		auto run() -> int;
		auto quit() -> void;

		Signal<void()> frame;

	private:
		bool running{false};
	};
}
