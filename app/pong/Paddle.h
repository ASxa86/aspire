#pragma once

#include <aspire/scene/Rectangle.h>

class Paddle
{
public:
	explicit Paddle(aspire::scene::Node& x);

	auto setPosition(sf::Vector2f x) -> void;
	[[nodiscard]] auto getPosition() const -> sf::Vector2f;

	auto setSize(sf::Vector2f x) -> void;
	[[nodiscard]] auto getSize() const -> sf::Vector2f;

	auto setColor(sf::Color x) -> void;
	[[nodiscard]] auto getColor() const -> sf::Color;

private:
	aspire::scene::Rectangle* shape{};
};
