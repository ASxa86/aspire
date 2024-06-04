#pragma once

#include <aspire/Circle.h>
#include <aspire/CollisionCircle.h>
#include <aspire/Color.h>
#include <aspire/Entity.h>
#include <aspire/Position.h>

class Ball : public Entity
{
public:
	Ball(aspire::Engine& x);

	void setRadius(float x) const;
	float getRadius() const;

	void setColor(aspire::Color);
	Color getColor() const;

	void setSpeed(float x);
	float getSpeed() const;

private:
	aspire::Kinematic kinematic;
	aspire::Circle circle;
	aspire::CollisionCircle;
	float speed{};
};
