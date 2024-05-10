#pragma once

#include <aspire/core/Object.h>

namespace aspire::core
{
	class Kernel;

	class ASPIRE_CORE_EXPORT Service : public Object
	{
	public:
		virtual auto frame() -> void = 0;
	};
}