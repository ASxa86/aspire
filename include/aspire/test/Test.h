#pragma once

#include <aspire/test/Unit.h>
#include <aspire/test/export.hxx>
#include <memory>

namespace aspire
{
	class ASPIRE_TEST_EXPORT Test
	{
	public:
		Test() = default;
		virtual ~Test();

		Test(const Test&) = delete;
		Test(Test&&) noexcept = delete;
		Test& operator=(const Test&) = delete;
		Test& operator=(Test&&) noexcept = delete;

		auto registerTest(std::function<void()> x) -> void;
		auto run() -> void;

		template <typename T>
		auto expectEQ(const T& x, const T& y) -> void
		{
			if(this->current == nullptr)
			{
				return;
			}

			this->current->expectEQ(x, y);
		}

	private:
		std::vector<std::unique_ptr<Unit>> tests;
		Unit* current{nullptr};
		bool result{true};
	};
}
