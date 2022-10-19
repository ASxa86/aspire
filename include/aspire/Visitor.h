#pragma once

namespace aspire
{
	class Node;

	/// @brief The base visitor class for defining the visitor pattern that operates on Nodes.
	class Visitor
	{
	public:
		/// @brief This enumeration describes the mode of traversal when operating on nodes.
		enum class Traversal : int
		{
			Descend,
			Ascend
		};

		virtual ~Visitor() = default;

		/// @brief Delete copy constructor to prevent object slicing.
		/// @param x The visitor to be copied.
		Visitor(const Visitor& x) = delete;

		/// @brief Delete the copy assignment operator to prevent object slicing.
		/// @param x The visitor to be copied.
		/// @return Visitor&
		auto operator=(const Visitor& x) -> Visitor& = delete;

		/// @brief Delete move constructor to prevent object slicing.
		/// @param x The visitor to be moved.
		Visitor(Visitor&& x) noexcept = delete;

		/// @brief Delete the move assignment operator to prevent object slicing.
		/// @param x The visitor to be moved.
		/// @return Visitor&
		auto operator=(Visitor&& x) noexcept -> Visitor& = delete;

		/// @brief Defines the double-dispatch function to be accessed by a given Node type.
		/// @param x The node to be operated on by this visitor.
		/// @return void
		virtual auto visit(Node& x) -> void;

		/// @brief Set the traversal mode to be used when operating on a node.
		/// @param x The traversal mode to assign to this visitor.
		/// @return void
		auto setTraversal(Traversal x) noexcept -> void;

		/// @brief Get the traversal mode for this visitor.
		/// @return Traversal
		auto getTraversal() const noexcept -> Traversal;

	private:
		Traversal traversal{Traversal::Descend};
	};
}
