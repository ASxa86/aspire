#include <QGuiApplication>
#include <QQmlApplicationEngine>
#include <QQuickWindow>

int main(int argc, char** argv)
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