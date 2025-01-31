#include <QGuiApplication>
#include <QQmlApplicationEngine>

#include <aspire/FactoryQQmlComponent.h>
#include <aspire/ParseQmlTypes.h>

int main(int argc, char** argv)
{
	QGuiApplication app(argc, argv);

	QQmlApplicationEngine engine;
	QObject::connect(&engine, &QQmlApplicationEngine::objectCreationFailed, &app, [] { QCoreApplication::exit(-1); }, Qt::QueuedConnection);
	engine.loadFromModule("app.editor", "Main");

	// Populate the component factory with all Qml types.
	aspire::FactoryQQmlComponent factory{&engine};

	for(const auto& path : engine.importPathList())
	{
		aspire::ParseQmlTypes(path.toStdString(), factory);
	}

	return QGuiApplication::exec();
}
