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

		/// @brief Find the QQmlComponent registered for the given object.
		/// @param x The object to perform the search with.
		/// @return A pointer the the associated QQmlComponent. Nullptr if the component could not be found.
		auto findComponent(QObject* x) const -> QQmlComponent*;

		/// @brief Find the QQmlComponent registered for the given qml type name.
		/// @param x The type name to perform the search with.
		/// @return A pointer the the associated QQmlComponent. Nullptr if the component could not be found.
		auto findComponent(const std::string& x) const -> QQmlComponent*;

		/// @brief Find the QML name registered for the given QObject.
		/// @param x The runtime QObject to perform the search with.
		/// @return The QML name of the given object. Empty string if it doesn't exist.
		auto findQmlName(QObject* x) const -> std::string_view;

	private:
		// Contains a map between QObject type names and their qml names. (i.e. "QQuickRectangle" vs "Rectangle")
		std::map<std::string, std::string> qmlTypeMap;

		// Contains a map between the qml name and component.
		std::map<std::string, std::unique_ptr<QQmlComponent>> components;
		QQmlEngine* engine{};
	};
}