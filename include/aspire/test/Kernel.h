#pragma once

#include <aspire/test/Test.h>

namespace aspire
{
	class Kernel
	{
	public:
		Kernel();
		~Kernel();

		static auto Instance() -> Kernel*;

		auto run() -> int;

	private:
		std::vector<std::unique_ptr<aspire::Test>> tests;
	};
}