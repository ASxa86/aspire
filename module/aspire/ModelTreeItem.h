#pragma once

#include <QtQml/qqmlregistration.h>
#include <QStandardItemModel>
#include <aspire/export.hxx>

namespace aspire
{
	class ASPIRE_EXPORT ModelTreeItem : public QStandardItemModel
	{
		Q_OBJECT
		Q_PROPERTY(QObject* item READ getItem WRITE setItem NOTIFY itemChanged)
		QML_ELEMENT

	public:
		explicit ModelTreeItem(QObject* parent = nullptr);
		void setItem(QObject* x) noexcept;
		QObject* getItem() const noexcept;

	signals:
		void itemChanged(QObject*);

	private:
		void reload();
		QStandardItem* load(QObject*);
		QObject* item{};
	};
}