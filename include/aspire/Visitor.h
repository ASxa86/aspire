#pragma once

#include <aspire/export.hxx>
#include <limits>

namespace aspire
{
	class Node;
	class Camera;
	class Geometry;

	/// @brief The base visitor class for defining the visitor pattern that operates on Nodes.
	class ASPIRE_EXPORT Visitor
	{
	public:
		/// @brief This enumeration describes the mode of traversal when operating on nodes.
		enum class Traversal : int
		{
			Descend,
			Ascend
		};

		Visitor(unsigned int x = std::numeric_limits<unsigned int>::max());
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
		virtual auto visit(Camera& x) -> void;
		virtual auto visit(Geometry& x) -> void;

		/// @brief Set the traversal mode to be used when operating on a node.
		/// @param x The traversal mode to assign to this visitor.
		/// @return void
		auto setTraversal(Traversal x) noexcept -> void;

		/// @brief Get the traversal mode for this visitor.
		/// @return Traversal
		auto getTraversal() const noexcept -> Traversal;

		/// @brief Set the depth of traversal for the visiting node's children.
		/// @param x The depth of traversal.
		/// @return void
		auto setDepth(unsigned int x) noexcept -> void;

		/// @brief Get the depth of traversal.
		/// @return int
		auto getDepth() const noexcept -> int;

	protected:
		/// @brief Traverse the given node's children in the direct defined by Traversal.
		/// Invoke this function when overriding visit() if you want traversal to occur on nested children/parents.
		/// @param x The node to traverse.
		/// @return void.
		auto traverse(Node& x) -> void;

	private:
		unsigned int depth{std::numeric_limits<unsigned int>::max()};
		unsigned int depthCurrent{};
		Traversal traversal{Traversal::Descend};
	};
}
