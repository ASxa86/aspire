#include <aspire/ParseQmlTypes.h>

#include <private/qqmljstypedescriptionreader_p.h>
#include <QQmlComponent>
#include <set>

namespace
{
	const std::string PluginQmlType{"plugins.qmltypes"};
}

auto aspire::ParseQmlTypes(const std::filesystem::path& x, FactoryQQmlComponent& factory) -> void
{
	if(std::filesystem::is_directory(x) == false)
	{
		return;
	}

	for(const auto& entry : std::filesystem::recursive_directory_iterator(x))
	{
		const auto& path = entry.path();

		if(std::filesystem::is_regular_file(path) == false || path.extension() != ".qmltypes")
		{
			continue;
		}

		const auto filename = QString::fromStdString(path.string());
		QFile file{filename};

		if(file.open(QFile::OpenModeFlag::ReadOnly) == false)
		{
			return;
		}

		QQmlJSTypeDescriptionReader reader{filename, file.readAll()};

		QList<QQmlJSExportedScope> objects;
		QStringList dependencies;
		const auto result = reader(&objects, &dependencies);

		if(result == false)
		{
			return;
		}

		// Fill the map with unique types. Otherwise we will have types listed for every supported
		// version. We just want to be one and done.
		std::map<std::string, std::set<std::string>> qmlTypes;

		for(const auto& exported : objects)
		{
			for(auto& exp : exported.exports)
			{
				qmlTypes[exp.package().toStdString()].insert(exp.type().toStdString());
			}

			qDebug() << "Value Type: " << exported.scope->valueTypeName();
		}

		for(const auto& [module, types] : qmlTypes)
		{
			for(const auto& type : types)
			{
				factory.registerComponent(module, type);
			}
		}
	}
}
