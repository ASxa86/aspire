#include <aspire/ModelEntity.h>
#include <ranges>

using aspire::Entity;
using aspire::ModelEntity;

ModelEntity::ModelEntity(QObject* parent) : QAbstractListModel{parent}
{
	this->roles.insert(static_cast<int>(Roles::Rotation), "rotation");
}

auto ModelEntity::setCount(int x) noexcept -> void
{
	this->count = x;
	this->countChanged(this->count);
}

auto ModelEntity::rowCount(const QModelIndex& /*parent*/) const -> int
{
	return static_cast<int>(this->entities.size());
}

auto ModelEntity::data(const QModelIndex& index, int role) const -> QVariant
{
	if(index.isValid() == false)
	{
		return {};
	}

	const auto& entity = this->entities[index.row()];

	switch(static_cast<ModelEntity::Roles>(role))
	{
		case ModelEntity::Roles::Rotation:
			return entity.getRotation();
			break;

		default:
			break;
	}

	return {};
}

auto ModelEntity::roleNames() const -> QHash<int, QByteArray>
{
	return this->roles;
}

auto ModelEntity::classBegin() -> void
{
}

auto ModelEntity::componentComplete() -> void
{
	this->entities.resize(this->count);
	this->countChanged(this->rowCount());
}
