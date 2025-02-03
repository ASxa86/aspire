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

	std::map<std::string, QQmlType> filteredTypes;

	for(auto type : QQmlMetaType::qmlAllTypes())
	{
		filteredTypes.try_emplace(type.elementName().toStdString(), type);
	}

	for(const auto& [name, type] : filteredTypes)
	{
		auto component = std::make_unique<QQmlComponent>(this->engine, type.module(), type.elementName());

		if(component->isReady() == false)
		{
			continue;
		}

		qInfo() << "Loaded " << type.elementName() << " (" << type.typeName() << ")";
		this->components[type.module().toStdString()].emplace_back(std::move(component));
	}
}

FactoryComponent::~FactoryComponent()
{
	Singleton = nullptr;
}
