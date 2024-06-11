#include <aspire/scene/Rectangle.h>

#include <aspire/core/PimplImpl.h>
#include <SFML/Graphics/RectangleShape.hpp>

using aspire::scene::Rectangle;

struct Rectangle::Impl
{
	sf::RectangleShape shape;
	sf::Vector2f size;
	sf::Color color{sf::Color::White};
};

Rectangle::Rectangle() = default;
Rectangle::~Rectangle() = default;

auto Rectangle::setSize(sf::Vector2f x) noexcept -> void
{
	this->pimpl->size = x;
}

auto Rectangle::getSize() const noexcept -> sf::Vector2f
{
	return this->pimpl->size;
}

auto Rectangle::setColor(sf::Color x) noexcept -> void
{
	this->pimpl->color = x;
}

auto Rectangle::getColor() const noexcept -> sf::Color
{
	return this->pimpl->color;
}

auto Rectangle::onDraw(sf::RenderTarget& target, sf::RenderStates& states) -> void
{
	this->pimpl->shape.setSize(this->pimpl->size);
	this->pimpl->shape.setFillColor(this->pimpl->color);
	this->pimpl->shape.setPosition(-(this->pimpl->size / 2.0F));
	target.draw(this->pimpl->shape, states);
}
