#pragma once

#include <aspire/core/Object.h>
#include <aspire/core/Pimpl.h>
#include <aspire/scene/export.hxx>

namespace aspire::scene
{
	class ASPIRE_SCENE_EXPORT Node : public aspire::core::Object
	{
	public:
		Node();
		~Node() override;

		Node(const Node&) = delete;
		auto operator=(const Node&) = delete;

		Node(Node&&) noexcept = delete;
		auto operator=(Node&&) noexcept = delete;

		auto setX(int x) noexcept -> void;
		[[nodiscard]] auto getX() const noexcept -> int;

		auto setY(int x) noexcept -> void;
		[[nodiscard]] auto getY() const noexcept -> int;

		auto setHeight(int x) noexcept -> void;
		[[nodiscard]] auto getHeight() const noexcept -> int;

		auto setWidth(int x) noexcept -> void;
		[[nodiscard]] auto getWidth() const noexcept -> int;

		[[nodiscard]] auto childNodes() const noexcept -> std::vector<Node*>;

	private:
		struct Impl;
		Pimpl<Impl> pimpl;
	};
}