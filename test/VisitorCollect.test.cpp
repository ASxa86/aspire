#include <aspire/Camera.h>
#include <aspire/Geometry.h>
#include <aspire/Node.h>
#include <aspire/VisitorCollect.h>
#include <gtest/gtest.h>

TEST(VisitorCollect, collection)
{
	aspire::Node node;

	auto camera = node.addChild<aspire::Camera>();
	camera->addChild<aspire::Camera>();
	camera->addChild<aspire::Node>();
	camera->addChild<aspire::Geometry>();
	node.addChild(std::make_unique<aspire::Geometry>());

	aspire::VisitorCollector<aspire::Camera> visitCamera;
	node.accept(visitCamera);

	EXPECT_EQ(visitCamera.getCollection().size(), 1);

	aspire::VisitorCollector<aspire::Geometry> visitrGeometry{2};
	node.accept(visitrGeometry);

	EXPECT_EQ(visitrGeometry.getCollection().size(), 2);
}
