#pragma once

#include <aspire/core/Object.h>
#include <aspire/core/Pimpl.h>
#include <SFML/Graphics/RenderTarget.hpp>
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

		auto setPosition(sf::Vector2f x) noexcept -> void;
		[[nodiscard]] auto getPosition() const noexcept -> sf::Vector2f;

		auto setScale(sf::Vector2f x) noexcept -> void;
		[[nodiscard]] auto getScale() const noexcept -> sf::Vector2f;

		auto setRotation(float x) noexcept -> void;
		[[nodiscard]] auto getRotation() const noexcept -> float;

		[[nodiscard]] auto childNodes() const noexcept -> std::vector<Node*>;

		[[nodiscard]] auto getTransformLocal() const noexcept -> sf::Transform;
		[[nodiscard]] auto getTransformGlobal() const noexcept -> sf::Transform;

		auto draw(sf::RenderTarget& target, sf::RenderStates states = {}) -> void;

	private:
		virtual auto onDraw(sf::RenderTarget& target, sf::RenderStates& states) -> void;
		struct Impl;
		Pimpl<Impl> pimpl;
	};
}