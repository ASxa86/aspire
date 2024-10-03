#include <aspire/scene/NodeTransform.h>

using aspire::scene::NodeTransform;

auto NodeTransform::setMatrix(glm::mat4 x) noexcept -> void
{
	this->matrix = x;
	this->dirty<Node::Dirty::Matrix>();
}

auto NodeTransform::getMatrix() const noexcept -> glm::mat4
{
	return this->matrix;
}
