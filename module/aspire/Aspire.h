#pragma once

#include <aspire/Meters.h>
#include <qqmlintegration.h>
#include <QObject>

namespace aspire
{
	class Aspire : public QObject
	{
		Q_OBJECT
		QML_ELEMENT
		QML_SINGLETON

	public:
		Q_INVOKABLE Meters meters(double x) const noexcept;
	};
}