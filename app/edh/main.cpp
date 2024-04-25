#include <QGuiApplication>
#include <QQmlApplicationEngine>
#include <QQuickView>

int main(int argc, char** argv)
{
	const QGuiApplication app{argc, argv};

	QQuickView window{};

	constexpr auto width{1280};
	constexpr auto height{720};
	window.setWidth(width);
	window.setHeight(height);
	window.setTitle("Aspire EDH");
	window.engine()->addImportPath(":/");
	window.setSource(QUrl{"qrc:/aspire/edh/Main.qml"});
	window.show();

	return QGuiApplication::exec();
}