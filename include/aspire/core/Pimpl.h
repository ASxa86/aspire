#pragma once

#include <memory>

namespace aspire
{
	/// @brief Private Implementation. Useful for hiding implementation details and modifying code without changing the API.
	/// Modified from http://herbsutter.com/gotw/_101/
	template <typename T>
	class Pimpl
	{
	public:
		Pimpl();
		~Pimpl();

		Pimpl(const Pimpl&) = delete;
		auto operator=(const Pimpl&) -> Pimpl& = delete;

		Pimpl(Pimpl&&) noexcept = default;
		auto operator=(Pimpl&&) noexcept -> Pimpl& = default;

		template <typename... Args>
		Pimpl(Args&&...) noexcept;

		auto operator->() -> T*;
		auto operator->() const -> const T*;
		auto operator*() -> T&;

	private:
		std::unique_ptr<T> m;
	};
}
