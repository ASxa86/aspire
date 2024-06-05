#include "BatchRenderer.h"

#include <SFML/Graphics/RenderTarget.hpp>

using aspire::widget::BatchRenderer;

auto BatchRenderer::draw(sf::RenderTarget& target, sf::RenderStates state) const -> void
{
	target.draw(this->buffer, state);
}
