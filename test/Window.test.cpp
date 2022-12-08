#include <aspire/NodeGeometry.h>
#include <aspire/PrimitiveDrawArrays.h>
#include <aspire/Vertex.h>
#include <aspire/Window.h>
#include <gtest/gtest.h>

TEST(Graphics_Window, test)
{
	aspire::Traits traits;
	traits.title = "Window.test.cpp";
	aspire::Window window{traits};

	aspire::Node node{};
	auto geometry = node.addChild<aspire::NodeGeometry>();

	auto buffer = geometry->addBufferObject<aspire::Vertex>();
	auto vertices = buffer->getData();
	vertices.emplace_back(glm::vec3{-0.5F, -0.5F, 0.0F});
	vertices.emplace_back(glm::vec3{0.5F, -0.5F, 0.0F});
	vertices.emplace_back(glm::vec3{0.0F, 0.5F, 0.0F});

	geometry->addPrimitive<aspire::PrimitiveDrawArrays>(aspire::Primitive::Type::Triangles, 0, vertices.size());
	buffer->setData(std::move(vertices));

	window.setNode(node);

	window.run();
}
