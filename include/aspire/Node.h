#pragma once

#include <aspire/Visitor.h>
#include <aspire/export.hxx>
#include <memory>
#include <string>
#include <vector>

namespace aspire
{
	/// @brief The base class that all visitor operations can be performed on.
	class ASPIRE_EXPORT Node
	{
	public:
		Node() = default;
		virtual ~Node() = default;

		/// @brief Delete copy constructor to prevent object slicing. Use clone instead.
		/// @param x The node to be copied.
		Node(const Node& x) = delete;

		/// @brief Delete the copy assignment operator to prevent object slicing. Use clone instead.
		/// @param x The node to be copied.
		/// @return Node&
		auto operator=(const Node& x) -> Node& = delete;

		/// @brief Delete move constructor to prevent object slicing.
		/// @param x The node to be moved.
		Node(Node&&) noexcept = delete;

		/// @brief Delete the move assignment operator to prevent object slicing.
		/// @param x The node to be moved.
		/// @return Node&
		auto operator=(Node&&) noexcept -> Node& = delete;

		/// @brief Accepts a visitor to process this node.
		/// @param x The visitor to operate on this node.
		/// @return void
		virtual auto accept(Visitor& x) -> void;

		/// @brief Override to define the ascending traversal behavior of a node.
		/// @param x The visitor to ascend with.
		/// @return void
		virtual auto ascend(Visitor& x) -> void;

		/// @brief Override to define the descending traversal behavior of a node.
		/// @param x The visitor to descend with.
		/// @return void
		virtual auto descend(Visitor& x) -> void;

		/// @brief Defines an arbitrary name for this node.
		/// Useful for debugging, logging, and serialization among other things.
		/// @param x The name to apply to this node.
		auto setName(std::string_view x) -> void;

		/// @brief Get the arbitrary name assigned to this node.
		/// @return std::string_view
		auto getName() const noexcept -> std::string_view;

		/// @brief Get the pointer to the parent of this node.
		/// @return Node* Nullptr if this node is not a child of another node.
		auto getParent() const noexcept -> Node*;

		/// @brief Adds a child node to this node.
		/// @param x The node to be added as a child to this node.
		/// @return void
		auto addChild(std::unique_ptr<Node> x) -> void;

		/// @brief Get the collection of child nodes for this node.
		/// @return const std::vector<std::unique_ptr<Node>>&
		auto getChildren() const -> const std::vector<std::unique_ptr<Node>>&;

	private:
		std::vector<std::unique_ptr<Node>> children;
		std::string name;
		Node* parent{nullptr};
	};
}
