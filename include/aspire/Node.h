#pragma once

#include <aspire/Event.h>
#include <aspire/Program.h>
#include <aspire/State.h>
#include <aspire/export.hxx>
#include <boost/signals2/signal.hpp>
#include <memory>
#include <string>
#include <vector>

namespace aspire
{
	class Node;

	template <typename T>
	concept NodeType = std::is_base_of<Node, T>::value;

	/// @brief The base class that all visitor operations can be performed on.
	class ASPIRE_EXPORT Node
	{
	public:
		Node(std::string_view = {});
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

		template <NodeType T>
		auto addChild(std::string_view x = {})
		{
			auto child = std::make_unique<T>(x);
			auto c = child.get();
			this->addChild(std::move(child));
			return c;
		}

		/// @brief Get the collection of child nodes for this node.
		/// @return const std::vector<std::unique_ptr<Node>>&
		auto getChildren() const -> const std::vector<std::unique_ptr<Node>>&;

		template <typename T>
		auto getChildren() const -> std::vector<T*>
		{
			std::vector<T*> v;

			for(auto&& child : this->children)
			{
				const auto typeChild = dynamic_cast<T*>(child.get());

				if(typeChild != nullptr)
				{
					v.emplace_back(typeChild);
				}
			}

			return v;
		}

		/// @brief Redirects the given event to the correct event handling function.
		/// @param x The event to redirect.
		/// @return void
		virtual auto event(Event& x) -> void;

		/// @brief Override to handle the given mouse event.
		/// @param x The mouse event to handle.
		/// @return void
		virtual auto eventMouse(EventMouse& x) -> void;

		/// @brief Override to handle the given keyboard event.
		/// @param x The keyboard event to handle.
		/// @return void
		virtual auto eventKeyboard(EventKeyboard& x) -> void;

		/// @brief Override to process logic during the update traversal.
		/// Ensure Node::update() is called before/after the override logic to continue child traversal.
		/// @return void
		virtual auto update() -> void;

		/// @brief Override to process logic during the rendering traversal.
		/// Ensure Node::draw() is called before/after the override logic to continue child traversal.
		/// @return void
		virtual auto draw(aspire::State& x) -> void;

		auto connectUpdate(auto x)
		{
			return this->signalUpdate.connect(x);
		}

		auto connectDraw(auto x)
		{
			return this->signalDraw.connect(x);
		}

		auto getOrCreateProgram() -> aspire::Program*;

	private:
		std::vector<std::unique_ptr<Node>> children;
		std::unique_ptr<aspire::Program> program;
		boost::signals2::signal<void(aspire::State&)> signalDraw;
		boost::signals2::signal<void()> signalUpdate;
		std::string name;
		Node* parent{nullptr};
	};
}
