#include <QCommandLineParser>
#include <QFileSystemWatcher>
#include <QGuiApplication>
#include <QQmlApplicationEngine>
#include <QQuickView>

int main(int argc, char** argv)
{
	QGuiApplication app{argc, argv};

	QCommandLineParser parser;
	parser.setApplicationDescription("Aspire Edit");
	parser.addHelpOption();

	QCommandLineOption option{"f", "The file to edit.", "file"};
	parser.addOption(option);
	parser.process(app);

	if(!parser.isSet(option))
	{
		parser.showHelp();
		return EXIT_FAILURE;
	}

	QFileSystemWatcher watcher;

	QQuickView window{};
	// window.engine()->addImportPath("/Users/aaron/Developer/aspire/build/vcpkg_installed/arm64-osx-release/Qt6/qml");
	// window.engine()->addPluginPath("/Users/aaron/Developer/aspire/build/vcpkg_installed/arm64-osx-release/Qt6/plugins");

	window.setWidth(1280);
	window.setHeight(720);
	window.setTitle("Aspire Edit");

	const auto source = QUrl::fromLocalFile(parser.value(option));
	watcher.addPath(source.toLocalFile());
	window.setSource(source);

	window.show();

	QObject::connect(&watcher, &QFileSystemWatcher::fileChanged, &window,
					 [&window](const auto& path)
					 {
						 qDebug() << path << " changed!";
						 window.engine()->clearComponentCache();
						 window.setSource(path);
					 });

	return QGuiApplication::exec();
}