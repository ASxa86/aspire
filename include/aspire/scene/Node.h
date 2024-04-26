#pragma once

#include <aspire/scene/export.hxx>
#include <memory>
#include <vector>

namespace aspire::scene
{
	/// @brief This class defines the base class for all scene nodes and acts as a container for all node types.
	class ASPIRE_SCENE_EXPORT Node
	{
	public:
		Node() = default;
		virtual ~Node() = default;

		Node(const Node&) = delete;
		Node& operator=(const Node&) = delete;

		Node(Node&&) noexcept = delete;
		Node& operator=(Node&&) noexcept = delete;

		/// @brief Add the given node to this node and claim ownership.
		/// @param x The node to add to this node.
		auto addChild(std::unique_ptr<Node> x) -> void;

		/// @brief Get the children this node owns.
		/// @return The immutable list of children this node owns.
		[[nodiscard]] auto getChildren() const noexcept -> const std::vector<std::unique_ptr<Node>>&;

		/// @brief Get the owning parent of this node.
		/// @return The owning parent. Nullptr if this node is not a child of another node.
		[[nodiscard]] auto getParent() const noexcept -> Node*;

		/// @brief Removes this node from its parent and returns an owning pointer.
		/// @return The owning pointer of the removed node. Nullptr if the node couldn't be removed.
		auto remove() -> std::unique_ptr<Node>;

	private:
		std::vector<std::unique_ptr<Node>> children;
		Node* parent{};
	};
}