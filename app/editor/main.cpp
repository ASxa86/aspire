#include <QGuiApplication>
#include <QQmlApplicationEngine>

#include <aspire/FactoryComponent.h>

int main(int argc, char** argv)
{
	QGuiApplication app(argc, argv);

	QQmlApplicationEngine engine;

	// Populate the component factory with all Qml types.
	aspire::FactoryComponent factory{engine};

	QObject::connect(&engine, &QQmlApplicationEngine::objectCreationFailed, &app, [] { QCoreApplication::exit(-1); }, Qt::QueuedConnection);
	engine.loadFromModule("app.editor", "Main");

	return QGuiApplication::exec();
}
