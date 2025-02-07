#include <aspire/WriteFileQML.h>
#include <gtest/gtest.h>

#include <aspire/FactoryComponent.h>
#include <aspire/ItemView.h>

TEST(WriteFileQML, writeObject)
{
	auto* component = aspire::FactoryComponent::Instance()->findComponent("Rectangle");
	ASSERT_NE(component, nullptr);

	auto rectangle = std::unique_ptr<QQuickItem>(qobject_cast<QQuickItem*>(component->create()));
	ASSERT_NE(rectangle, nullptr);

	auto child = std::unique_ptr<QQuickItem>(qobject_cast<QQuickItem*>(component->create()));
	ASSERT_NE(child, nullptr);

	child->setParentItem(rectangle.get());
	child->setParent(rectangle.get());

	const std::filesystem::path qmlfile{"test.qml"};
	aspire::WriteFileQML(rectangle.get(), qmlfile);
	EXPECT_TRUE(std::filesystem::exists(qmlfile));
	// EXPECT_TRUE(std::filesystem::remove(qmlfile));
}
