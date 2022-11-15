#include <aspire/NodeGeometry.h>

using aspire::NodeGeometry;

auto NodeGeometry::draw() -> void
{
	for(auto&& primitive : this->primitives)
	{
		primitive->draw();
	}
}

auto NodeGeometry::addPrimitive(std::unique_ptr<Primitive> x) -> void
{
	this->primitives.emplace_back(std::move(x));
}
