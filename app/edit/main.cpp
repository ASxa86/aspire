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
	window.engine()->addImportPath(":/");
	window.setSource(QUrl{"qrc:/aspire/edit/Main.qml"});
	window.show();

	return QGuiApplication::exec();
}