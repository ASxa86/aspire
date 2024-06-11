#pragma once

#include <aspire/scene/Node.h>

namespace aspire::scene
{
	class ASPIRE_SCENE_EXPORT Rectangle : public Node
	{
	public:
		Rectangle();
		~Rectangle() override;

		auto setSize(sf::Vector2f x) noexcept -> void;
		[[nodiscard]] auto getSize() const noexcept -> sf::Vector2f;

		auto setColor(sf::Color x) noexcept -> void;
		[[nodiscard]] auto getColor() const noexcept -> sf::Color;

	private:
		auto onDraw(sf::RenderTarget& target, sf::RenderStates& states) -> void override;
		struct Impl;
		Pimpl<Impl> pimpl;
	};
}
