#include "Paddle.h"

Paddle::Paddle(aspire::scene::Node& root) : shape{root.createChild<aspire::scene::Rectangle>()}
{
}

auto Paddle::setPosition(sf::Vector2f x) -> void
{
	this->shape->setPosition(x);
}

auto Paddle::getPosition() const -> sf::Vector2f
{
	return this->shape->getPosition();
}

auto Paddle::setSize(sf::Vector2f x) -> void
{
	this->shape->setSize(x);
}

auto Paddle::getSize() const -> sf::Vector2f
{
	return this->shape->getSize();
}

auto Paddle::setColor(sf::Color x) -> void
{
	this->shape->setColor(x);
}

auto Paddle::getColor() const -> sf::Color
{
	return this->shape->getColor();
}
