#pragma once

#include <QObject>
#include <QtQmlIntegration>
#include <aspire/export.hxx>

namespace aspire
{
	class ASPIRE_EXPORT Aspire : public QObject
	{
		Q_OBJECT
		QML_ELEMENT
		QML_SINGLETON

	public:
		Aspire(QObject* parent = nullptr);

	private:
	};
}
