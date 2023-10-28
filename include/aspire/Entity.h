#pragma once

#include <QQuickItem>
#include <aspire/export.hxx>

namespace aspire
{
	class ASPIRE_EXPORT Entity
	{
		Q_GADGET
		Q_PROPERTY(double rotation READ getRotation WRITE setRotation NOTIFY rotationChanged)
		QML_VALUE_TYPE(entity)

	public:
		auto setRotation(double x) noexcept -> void;
		auto getRotation() const noexcept -> double;

		auto operator<=>(const Entity&) const noexcept = default;

	private:
		double rotation{};
	};
}