#pragma once

#include <SFML/Graphics/Drawable.hpp>
#include <SFML/Graphics/VertexBuffer.hpp>

namespace aspire::widget
{
	class BatchRenderer : public sf::Drawable
	{
	public:
		auto draw(sf::RenderTarget& target, sf::RenderStates states) const -> void override;

	private:
		sf::VertexBuffer buffer;
	};
}
