#pragma once

#include <aspire/core/Object.h>
#include <aspire/core/export.hxx>

namespace aspire::core
{
	class ASPIRE_CORE_EXPORT Kernel : public Object
	{
	public:
		auto run() -> int;

	private:
	};
}