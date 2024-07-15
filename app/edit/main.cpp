#include <QGuiApplication>
#include <QQmlApplicationEngine>
#include <QQuickView>

int main(int argc, char** argv)
{
	QGuiApplication app{argc, argv};

	QQuickView window{};

	window.setWidth(1280);
	window.setHeight(720);
	window.setTitle("Aspire Edit");

	window.loadFromModule("qml.aspire-edit", "Main");
	window.show();

	return QGuiApplication::exec();
}