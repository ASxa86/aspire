#pragma once

#include <utility>

///	\brief Private Implementation. Useful for hiding implementation details and modifying code without changing the API.
///	Modified from http://herbsutter.com/gotw/_101/
template <typename T>
Pimpl<T>::Pimpl() : m{std::make_unique<T>()}
{
}

template <typename T>
template <typename... Args>
Pimpl<T>::Pimpl(Args&&... args) noexcept : m{std::make_unique<T>(std::forward<Args>(args)...)}
{
}

template <typename T>
Pimpl<T>::~Pimpl()
{
}

template <typename T>
auto Pimpl<T>::operator->() -> T*
{
	return m.get();
}

template <typename T>
auto Pimpl<T>::operator->() const -> const T*
{
	return m.get();
}

template <typename T>
auto Pimpl<T>::operator*() -> T&
{
	return *m.get();
}