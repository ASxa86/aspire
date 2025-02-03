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
		struct Key
		{
			std::string elementName;
			std::string typeName;
		};

		struct KeyCompare
		{
			using is_transparent = void;

			bool operator()(const Key& lhs, const Key& rhs) const
			{
				return lhs.elementName < rhs.elementName && lhs.typeName < rhs.elementName;
			}

			bool operator()(const Key& lhs, const std::string& rhs) const
			{
				return lhs.elementName < rhs && lhs.typeName < rhs;
			}

			bool operator()(const std::string& lhs, const Key& rhs) const
			{
				return lhs < rhs.elementName && lhs < rhs.typeName;
			}
		};

		std::map<Key, std::unique_ptr<QQmlComponent>, KeyCompare> components;
		QQmlEngine* engine{};
	};
}