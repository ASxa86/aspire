#pragma once

#include <aspire/core/EnumMask.h>
#include <aspire/core/Object.h>
#include <aspire/core/Pimpl.h>
#include <aspire/scene/export.hxx>
#include <sigslot/signal.hpp>

namespace aspire::scene
{
	class ASPIRE_SCENE_EXPORT Node
	{
	public:
		enum class Dirty : std::uint8_t
		{
			NodeAdded = 0b00000001,
			NodeRemoved = 0b00000010,
			Geometry = 0b00000100,
			Matrix = 0b00001000
		};

		Node();
		virtual ~Node();

		Node(const Node&) = delete;
		auto operator=(const Node&) = delete;

		Node(Node&&) noexcept = delete;
		auto operator=(Node&&) noexcept = delete;

		auto parent() const noexcept -> Node*;
		auto insertChildAfter(Node* x, std::unique_ptr<Node> node) -> void;
		auto insertChildBefore(Node* x, std::unique_ptr<Node> node) -> void;
		auto addChild(std::unique_ptr<Node> x) -> void;
		auto remove() -> void;

		/// @brief Notify the root node in the scene graph that this node has changed.
		/// @param x The node state that was modified.
		auto dirty(aspire::core::EnumMask<Dirty> x) noexcept -> void;

		template <Dirty E>
		auto dirty() noexcept
		{
			this->dirty(aspire::core::EnumMask<Dirty>{E});
		}

		[[nodiscard]] auto children() const noexcept -> const std::vector<std::unique_ptr<Node>>&;

		auto onDirty(std::function<void(Node*, aspire::core::EnumMask<Dirty>)> x) -> sigslot::connection;

	private:
		struct Impl;
		Pimpl<Impl> pimpl;
	};
}
