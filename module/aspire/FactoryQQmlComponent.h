#pragma once

#include <QQmlComponent>
#include <QQmlEngine>
#include <aspire/export.hxx>
#include <set>
#include <string_view>

namespace aspire
{
	class ASPIRE_EXPORT FactoryQQmlComponent
	{
	public:
		static constexpr std::string_view TypeName{"FactoryQQmlCOmponent"};

		FactoryQQmlComponent(QQmlEngine* engine);
		~FactoryQQmlComponent();

		FactoryQQmlComponent(const FactoryQQmlComponent&) = delete;
		FactoryQQmlComponent& operator=(const FactoryQQmlComponent&) = delete;

		FactoryQQmlComponent(FactoryQQmlComponent&&) noexcept = default;
		FactoryQQmlComponent& operator=(FactoryQQmlComponent&&) noexcept = default;

		static auto Instance() -> FactoryQQmlComponent*;

		auto registerComponent(QAnyStringView module, QAnyStringView type) -> void;

	private:
		std::map<std::string, std::set<std::unique_ptr<QQmlComponent>>> components;
		QQmlEngine* engine{};
	};
}