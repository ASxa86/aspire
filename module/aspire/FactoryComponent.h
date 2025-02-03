#pragma once

#include <QQmlComponent>
#include <QQmlEngine>
#include <aspire/export.hxx>
#include <string_view>

namespace aspire
{
	class ASPIRE_EXPORT FactoryComponent
	{
	public:
		FactoryComponent(QQmlEngine* engine);
		~FactoryComponent();

		FactoryComponent(const FactoryComponent&) = delete;
		FactoryComponent& operator=(const FactoryComponent&) = delete;

		FactoryComponent(FactoryComponent&&) noexcept = default;
		FactoryComponent& operator=(FactoryComponent&&) noexcept = default;

		static auto Instance() -> FactoryComponent*;

	private:
		std::map<std::string, std::vector<std::unique_ptr<QQmlComponent>>> components;
		QQmlEngine* engine{};
	};
}