#include <aspire/NodeGeometry.h>
#include <aspire/PrimitiveDrawArrays.h>
#include <aspire/Window.h>
#include <gtest/gtest.h>

TEST(Graphics_Window, test)
{
	aspire::Traits traits;
	traits.title = "Window.test.cpp";
	aspire::Window window{traits};

	aspire::Node node{};

	auto geometry = node.addChild<aspire::NodeGeometry>();

	auto vertices = geometry->getVertices();
	vertices.push_back({{-0.5F, -0.5F, 0.0F}});
	vertices.push_back({{0.5F, -0.5F, 0.0F}});
	vertices.push_back({{0.0F, 0.5F, 0.0F}});
	geometry->setVertices(vertices);
	geometry->addPrimitive<aspire::PrimitiveDrawArrays>(aspire::Primitive::Type::Triangles, 0, vertices.size());

	window.setNode(node);

	window.run();
}
