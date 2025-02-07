#include <aspire/FactoryComponent.h>
#include <gtest/gtest.h>
#include <QCoreApplication>
#include <QQmlApplicationEngine>

int main(int argc, char** argv)
{
	const QCoreApplication app{argc, argv};

	QQmlApplicationEngine engine;

	aspire::FactoryComponent factory{engine};

	testing::InitGoogleTest(&argc, argv);

	return ::RUN_ALL_TESTS();
}