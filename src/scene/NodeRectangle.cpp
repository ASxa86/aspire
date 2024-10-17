#include <aspire/scene/NodeRectangle.h>

using aspire::scene::NodeRectangle;

namespace
{
	auto BuildRectangle(glm::vec4 color, glm::vec2 position, glm::vec2 size)
	{
		// 0-------------3
		// |           / |
		// |        /    |
		// |     /       |
		// |  /          |
		// 1-------------2
		// Rectangle vertices;

		const auto left = position.x;
		const auto top = position.y;
		const auto bottom = position.y + size.y;
		const auto right = position.x + size.x;

		NodeRectangle::Vertex v0{.position = {left, top}, .color = color};
		NodeRectangle::Vertex v1{.position = {left, bottom}, .color = color};
		NodeRectangle::Vertex v2{.position = {right, bottom}, .color = color};
		NodeRectangle::Vertex v3{.position = {right, top}, .color = color};

		return std::vector{v0, v1, v3, v1, v2, v3};
	}
}

auto NodeRectangle::setColor(glm::vec4 x) noexcept -> void
{
	this->color = x;
	this->setVertices(BuildRectangle(this->color, this->position, this->size));
}

auto NodeRectangle::getColor() const noexcept -> glm::vec4
{
	return this->color;
}

auto NodeRectangle::setPosition(glm::vec2 x) noexcept -> void
{
	this->position = x;
	this->setVertices(BuildRectangle(this->color, this->position, this->size));
}

auto NodeRectangle::getPosition() const noexcept -> glm::vec2
{
	return this->position;
}

auto NodeRectangle::setSize(glm::vec2 x) noexcept -> void
{
	this->size = x;
	this->setVertices(BuildRectangle(this->color, this->position, this->size));
}

auto NodeRectangle::getSize() const noexcept -> glm::vec2
{
	return this->size;
}
