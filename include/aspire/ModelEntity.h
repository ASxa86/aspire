#pragma once

#include <aspire/Entity.h>
#include <QAbstractListModel>
#include <QQmlParserStatus>

namespace aspire
{
	class ASPIRE_EXPORT ModelEntity : public QAbstractListModel, public QQmlParserStatus
	{
		Q_OBJECT
		Q_INTERFACES(QQmlParserStatus)
		Q_PROPERTY(int count READ rowCount WRITE setCount NOTIFY countChanged)
		QML_ELEMENT

	public:
		enum class Roles : int
		{
			Rotation
		};

		explicit ModelEntity(QObject *parent = nullptr);

		auto setCount(int x) noexcept -> void;
		auto rowCount(const QModelIndex &parent = QModelIndex()) const -> int override;
		auto data(const QModelIndex &index, int role = Qt::DisplayRole) const -> QVariant override;
		auto roleNames() const -> QHash<int, QByteArray> override;
		auto classBegin() -> void override;
		auto componentComplete() -> void override;

	signals:
		auto countChanged(int) -> void;

	private:
		std::vector<Entity> entities;
		QHash<int, QByteArray> roles;
		int count{};
	};
}