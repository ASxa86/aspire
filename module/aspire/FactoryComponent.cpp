#include <aspire/FactoryComponent.h>

#include <private/qqmlmetatype_p.h>

using aspire::FactoryComponent;

namespace
{
	FactoryComponent* Singleton{nullptr};
}

auto FactoryComponent::Instance() -> FactoryComponent*
{
	return Singleton;
}

FactoryComponent::FactoryComponent(QQmlEngine* engine) : engine{engine}
{
	Singleton = this;

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
		auto component = std::make_unique<QQmlComponent>(this->engine, type.module(), type.elementName());

		if(component->isReady() == false)
		{
			continue;
		}

		qInfo() << "Loaded " << type.elementName() << " (" << type.typeName() << ")";
		Key key{.elementName = type.elementName().toStdString(), .typeName = type.typeName().toStdString()};
		this->components[std::move(key)] = std::move(component);
	}

	auto foundIt = this->components.find(std::string("Rectangle"));

	if(foundIt != std::end(this->components))
	{
		auto& c = foundIt->second;
		auto* object = c->create();
		auto type = QQmlMetaType::qmlType(object->metaObject());
		qDebug() << "Found " << type.elementName() << ", " << type.typeName();

		delete object;
	}
}

FactoryComponent::~FactoryComponent()
{
	Singleton = nullptr;
}
