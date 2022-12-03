#pragma once

#include <aspire/Primitive.h>

namespace aspire
{
	/// @brief Defines a primitive to render bound data buffers as an OpenGL draw array.
	class ASPIRE_EXPORT PrimitiveDrawArrays : public Primitive
	{
	public:
		/// @brief Initialize this primitive.
		/// @param type The primitive used to render the bound buffers.
		/// @param first The starting index in the buffer.
		/// @param count The number of indices to be rendered.
		PrimitiveDrawArrays(Primitive::Type type, int first, std::size_t count);

		/// @brief Set the index in the buffer to begin rendering at.
		/// @param x The starting index in the buffer.
		auto setFirst(int x) -> void;

		/// @brief Get the index that the bound buffer will begin rendering from.
		/// @return The stargting index in the buffer.
		auto getFirst() const -> int;

		/// @brief Set the number of indices to be rendered.
		/// @param x The number of indices to be rendered.
		auto setCount(std::size_t x) -> void;

		/// @brief Get the number of indices to be rendered.
		/// @return The number of indices to be rendered.
		auto getCount() const -> std::size_t;

		/// @brief Overriden to implement glDrawArrays.
		auto draw() -> void override;

	private:
		int first{};
		std::size_t count{};
	};
}
