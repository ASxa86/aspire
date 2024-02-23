#pragma once

#include <aspire/test/export.hxx>
#include <functional>

namespace aspire
{
	/// @brief This class represents a single unit of testing.
	class ASPIRE_TEST_EXPORT Unit
	{
	public:
		explicit Unit(std::function<void()> x);

		/// @brief Run the unit invoking the registered function.
		auto run() -> void;

		template <typename T>
		auto expectEQ(const T& x, const T& y) -> void
		{
			this->result &= (x == y);
		}

		auto getResult() const noexcept -> bool;

	private:
		std::function<void()> test;
		bool result{true};
	};
}