#pragma once

#include <aspire/export.hxx>
#include <qqmlintegration.h>
#include <QObject>

namespace aspire
{
	class ASPIRE_EXPORT Meters
	{
		Q_GADGET
		QML_VALUE_TYPE(meters)

	public:
		Meters() noexcept = default;
		explicit Meters(double x) noexcept;
		Q_INVOKABLE [[nodiscard]] double toDouble() const noexcept;
		Q_INVOKABLE [[nodiscard]] QString toString() const;

	private:
		double value{};
	};
}
