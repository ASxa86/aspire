#pragma once

#include <aspire/Visitor.h>
#include <aspire/export.hxx>
#include <string>

namespace aspire
{
	/// @brief The base class that all visitor operations can be performed on.
	class ASPIRE_EXPORT Node
	{
	public:
		virtual ~Node() = default;

		/// @brief Accepts a visitor to process this node.
		/// @param x The visitor to operate on this node.
		virtual void accept(Visitor& x);

		/// @brief Defines an arbitrary name for this node.
		/// Useful for debugging, logging, and serialization among other things.
		/// @param x The name to apply to this node.
		void setName(std::string_view x);

		/// @brief Get the arbitrary name assigned to this node.
		/// @return std::string_view
		std::string_view getName() const noexcept;

	private:
		std::string name;
	};
}
