#include <aspire/NodeGeometry.h>

using aspire::NodeGeometry;

auto NodeGeometry::draw() -> void
{
	this->vbo.bind();

	for(auto&& primitive : this->primitives)
	{
		primitive->draw();
	}
}

auto NodeGeometry::addPrimitive(std::unique_ptr<Primitive> x) -> void
{
	this->primitives.emplace_back(std::move(x));
}

auto NodeGeometry::setVertices(std::vector<aspire::Vertex> x) -> void
{
	this->vbo.setVertices(std::move(x));
}

auto NodeGeometry::getVertices() const -> const std::vector<aspire::Vertex>&
{
	return this->vbo.getVertices();
}
