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
	return this->findComponent(std::string{this->findQmlName(x)});
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

auto FactoryComponent::findQmlName(QObject* x) const -> std::string_view
{
	if(x == nullptr)
	{
		return {};
	}

	const auto foundIt = this->qmlTypeMap.find(x->metaObject()->className());

	if(foundIt == std::end(this->qmlTypeMap))
	{
		return {};
	}

	return foundIt->second;
}
