#pragma once

#include <type_traits>

namespace aspire
{
	/// @brief Type-safe implementation for handling scoped enumerations as bitmasks.
	/// @tparam T An enumeration type.
	template <typename T> requires std::is_enum<T>::value
	class Bitmask
	{
	public:
		using UnderlyingType = std::underlying_type<T>::type;

		/// @brief Add the given enumeration value to the bitmask.
		/// @param x The enumeration to add.
		void add(T x)
		{
			this->bits |= static_cast<UnderlyingType>(x);
		}

		/// @brief Remove the given enumeration value from the bitmask.
		/// @param x The enumeration to remove.
		void remove(T x)
		{
			this->bits &= ~static_cast<UnderlyingType>(x);
		}

		/// @brief Test the given enumeration to determine if it exists within the bitmask.
		/// @param x The enumeration to test.
		/// @return bool True if the enumeration exists.
		bool test(T x) const
		{
			return (this->bits & static_cast<UnderlyingType>(x)) != UnderlyingType{};
		}

		/// @brief Get the underlying bitmask value of this object.
		/// @return std::underlying_type<T> The bitmask of the enumeration's underlying type.
		UnderlyingType get() const
		{
			return this->bits;
		}

	private:
		UnderlyingType bits{};
	};
}
