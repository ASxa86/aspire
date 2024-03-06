#include <QGuiApplication>
#include <QQmlApplicationEngine>
#include <QQuickWindow>

auto main(int argc, char** argv) -> int
{
	QGuiApplication app{argc, argv};

	QSurfaceFormat format;
	format.setSwapInterval(0);
	format.setSamples(8);
	QSurfaceFormat::setDefaultFormat(format);

	QQmlApplicationEngine engine;
	engine.load(QUrl::fromLocalFile(MAIN_QML));

	return QGuiApplication::exec();
}