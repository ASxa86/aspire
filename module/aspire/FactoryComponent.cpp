#include <aspire/FactoryComponent.h>

#include <private/qqmlmetatype_p.h>
#include <filesystem>
#include <fstream>
#include <set>

#include <QQuickItem>

using aspire::FactoryComponent;

namespace
{
	FactoryComponent* Singleton{nullptr};

	// Split string into a list of space-separated strings.
	std::vector<std::string_view> split(std::string_view x)
	{
		std::vector<std::string_view> v;

		auto startIt = std::begin(x);

		for(auto it = startIt; it != std::end(x); ++it)
		{
			if(*it != ' ')
			{
				continue;
			}

			v.emplace_back(startIt, it);
			startIt = ++it;
		}

		v.emplace_back(startIt, std::end(x));

		return v;
	}
}

auto FactoryComponent::Instance() -> FactoryComponent*
{
	return Singleton;
}

FactoryComponent::FactoryComponent(QQmlApplicationEngine& x) : engine{&x}
{
	Singleton = this;

	// Parse all given import path lists for directories containing the qmldir file.
	// This is done to parse the known "module <module name>" from the file.
	// This blanket parse also pulls in impl and style modules that aren't necessary by default.
	// Therefore, a separate optional list is parsed to to clean up any modules we don't want to load
	// oursleves.

	this->engine->loadFromModule("QtQuick.Controls", "");
	this->engine->loadFromModule("QtQuick.Layouts", "");
	this->engine->loadFromModule("QtQuick", "");
	this->engine->loadFromModule("QtQml.Models", "");
	this->engine->loadFromModule("aspire", "");

	// std::set<std::string> importList;
	// std::set<std::string> optionalList;

	// for(const auto& plugin : this->engine->importPathList())
	//{
	//	std::filesystem::path dir{plugin.toStdString()};

	//	if(std::filesystem::is_directory(dir) == false)
	//	{
	//		continue;
	//	}

	//	for(const auto& entry : std::filesystem::recursive_directory_iterator{dir})
	//	{
	//		const auto& path = entry.path();

	//		if(std::filesystem::is_regular_file(path) == false)
	//		{
	//			continue;
	//		}

	//		if(path.filename() != "qmldir")
	//		{
	//			continue;
	//		}

	//		// Parse the qmldir file.
	//		std::ifstream qmldir{path};

	//		if(qmldir.is_open() == false)
	//		{
	//			continue;
	//		}

	//		std::string line;
	//		while(std::getline(qmldir, line))
	//		{
	//			if(std::empty(line) == true)
	//			{
	//				continue;
	//			}

	//			const auto tokens = split(line);

	//			if(std::size(tokens) == 2 && tokens[0] == "module" && tokens[1].ends_with("impl") == false)
	//			{
	//				importList.insert(std::string{tokens[1]});
	//			}

	//			if(std::size(tokens) >= 3 && (tokens[0] == "optional" || tokens[0] == "default"))
	//			{
	//				optionalList.insert(std::string{tokens[2]});
	//			}
	//		}
	//	}
	//}

	//// Clean up modules we don't want to import.
	// for(const auto& optional : optionalList)
	//{
	//	importList.erase(optional);
	// }

	// for(const auto& module : importList)
	//{
	//	qDebug() << "Loading module: " << module;
	//	this->engine->loadFromModule(module, "");
	// }

	// qmlAllTypes() provides the same types for different versions. To deduplicate these
	// use a map to filter down to just the latest version which qmlAllTypes lists in descending order.
	std::map<QString, QQmlType> filteredTypes;

	for(auto type : QQmlMetaType::qmlAllTypes())
	{
		filteredTypes.try_emplace(type.elementName(), type);
	}

	// Once filtered, store the QQmlType as its element and type name to enable
	// querying via element or type name.
	for(const auto& [name, type] : filteredTypes)
	{
		qDebug() << "Loading " << type.elementName();
		auto component = std::make_unique<QQmlComponent>(this->engine, type.module(), type.elementName());

		// if(component->isReady() == false)
		//{
		//	continue;
		// }

		const auto elementName = type.elementName().toStdString();
		const auto typeName = type.typeName().toStdString();

		this->qmlTypeMap[typeName] = elementName;
		qInfo() << "Loaded " << type.elementName() << " to " << type.typeName();
		this->components[elementName] = std::move(component);
	}
}

FactoryComponent::~FactoryComponent()
{
	Singleton = nullptr;
}

auto FactoryComponent::findComponent(QObject* x) const -> QQmlComponent*
{
	return this->findComponent(std::string{this->findQmlName(x->metaObject())});
}

auto FactoryComponent::findComponent(const std::string& x) const -> QQmlComponent*
{
	if(std::empty(x) == true)
	{
		return nullptr;
	}

	const auto foundIt = this->components.find(x);

	if(foundIt == std::end(this->components))
	{
		return nullptr;
	}

	return foundIt->second.get();
}

auto FactoryComponent::findQmlName(const QMetaObject* x) const -> std::string_view
{
	if(x == nullptr)
	{
		return {};
	}

	const auto foundIt = this->qmlTypeMap.find(x->className());

	if(foundIt == std::end(this->qmlTypeMap))
	{
		return {};
	}

	return foundIt->second;
}
