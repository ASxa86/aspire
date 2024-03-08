#pragma once

#include <QQuickItem>
#include <aspire/export.hxx>

namespace aspire
{
	class ASPIRE_EXPORT Entity
	{
		Q_GADGET
		Q_PROPERTY(int id READ getID WRITE setID)
		Q_PROPERTY(double rotation READ getRotation WRITE setRotation NOTIFY rotationChanged)
		QML_VALUE_TYPE(entity)

	public:
		Entity() = default;
		Entity(int x);
		~Entity() = default;

		Entity(const Entity&) = default;
		auto operator=(const Entity&) -> Entity& = default;

		Entity(Entity&&) noexcept = default;
		auto operator=(Entity&&) noexcept -> Entity& = default;

		auto setID(int x) noexcept -> void;
		[[nodiscard]] auto getID() const noexcept -> int;

		auto setRotation(double x) noexcept -> void;
		[[nodiscard]] auto getRotation() const noexcept -> double;

		auto operator<=>(const Entity&) const noexcept = default;

	private:
		int id{};
		double rotation{};
	};
}