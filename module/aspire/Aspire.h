#pragma once

#include <aspire/WriteFileQML.h>
#include <qqmlintegration.h>
#include <QObject>
#include <QUrl>
#include <aspire/export.hxx>


namespace aspire
{
	class ASPIRE_EXPORT Aspire : public QObject
	{
		Q_OBJECT
		QML_SINGLETON
		QML_ELEMENT

	public:
		Q_INVOKABLE void writeFile(QObject* object, const QUrl& url) const;

	private:
	};
}