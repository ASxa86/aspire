#include <QGuiApplication>
#include <QQmlApplicationEngine>
#include <QQuickWindow>

auto main(int argc, char** argv) -> int
{
	QGuiApplication app{argc, argv};

	constexpr auto defaultSwapInterval{0};
	constexpr auto defaultSamples{8};

	QSurfaceFormat format;
	format.setSwapInterval(defaultSwapInterval);
	format.setSamples(defaultSamples);
	QSurfaceFormat::setDefaultFormat(format);

	QQmlApplicationEngine engine;
	engine.load(QUrl::fromLocalFile(MAIN_QML));

	return QGuiApplication::exec();
}