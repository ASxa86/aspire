#include <aspire/FactoryQQmlComponent.h>

using aspire::FactoryQQmlComponent;

namespace
{
	FactoryQQmlComponent* Singleton{nullptr};
}

auto FactoryQQmlComponent::Instance() -> FactoryQQmlComponent*
{
	return Singleton;
}

FactoryQQmlComponent::FactoryQQmlComponent(QQmlEngine* engine) : engine{engine}
{
	Singleton = this;
}

FactoryQQmlComponent::~FactoryQQmlComponent()
{
	Singleton = nullptr;
}

auto FactoryQQmlComponent::registerComponent(QAnyStringView module, QAnyStringView type) -> void
{
	auto component = std::make_unique<QQmlComponent>(this->engine, module, type);

	if(component->isReady() == true)
	{
		this->components[module.toString().toStdString()].insert(std::move(component));
	}
}