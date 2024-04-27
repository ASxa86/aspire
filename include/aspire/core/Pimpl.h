#pragma once

#include <memory>

///	\brief Private Implementation. Useful for hiding implementation details and modifying code without changing the API.
///	Modified from http://herbsutter.com/gotw/_101/
template <typename T>
class Pimpl
{
public:
	Pimpl();

	template <typename... Args>
	Pimpl(Args&&...) noexcept;

	~Pimpl();

	auto operator->() -> T*;

	auto operator->() const -> const T*;

	auto operator*() -> T&;

private:
	std::unique_ptr<T> m;
};
