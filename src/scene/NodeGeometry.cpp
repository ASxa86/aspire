#include <aspire/scene/NodeGeometry.h>

using aspire::scene::NodeGeometry;

auto NodeGeometry::setVertices(std::vector<Vertex> x) -> void
{
	this->vertices = std::move(x);
	this->dirty<Node::Dirty::Geometry>();
}

auto NodeGeometry::getVertices() const noexcept -> const std::vector<Vertex>&
{
	return this->vertices;
}
