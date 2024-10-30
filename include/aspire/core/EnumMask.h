#pragma once

#include <aspire/core/Concept.h>
#include <initializer_list>

namespace aspire::core
{
	template <TypeEnum T>
	class EnumMask
	{
	public:
		using UnderlyingType = std::underlying_type_t<T>;

		EnumMask() = default;

		explicit EnumMask(std::initializer_list<T> x)
		{
			for(auto e : x)
			{
				this->set(e);
			}
		}

		auto test(T x) const noexcept -> bool
		{
			return (this->mask & static_cast<UnderlyingType>(x)) != 0;
		}

		auto set(T x) noexcept -> void
		{
			this->mask |= static_cast<UnderlyingType>(x);
		}

		auto remove(T x) noexcept -> void
		{
			this->mask &= ~static_cast<UnderlyingType>(x);
		}

		auto flip(T x) noexcept -> void
		{
			this->mask ^= static_cast<UnderlyingType>(x);
		}

		auto clear() noexcept -> void
		{
			this->mask = 0;
		}

	private:
		UnderlyingType mask{};
	};
}
