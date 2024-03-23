#include <aspire/ModelEntity.h>

using aspire::Entity;
using aspire::ModelEntity;

ModelEntity::ModelEntity(QObject* parent) : QAbstractListModel{parent}
{
	this->roles.insert(static_cast<int>(Roles::ID), "id");
	this->roles.insert(static_cast<int>(Roles::Rotation), "rotation");
}

auto ModelEntity::setRotation(double x) noexcept -> void
{
	if(this->rotation != x)
	{
		this->rotation = x;
		this->rotationChanged(this->rotation);
	}
}

auto ModelEntity::getRotation() const noexcept -> double
{
	return this->rotation;
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
		case ModelEntity::Roles::ID:
			return entity.getID();
			break;

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
	this->entities.reserve(this->count);

	for(auto i = 0; i < this->count; i++)
	{
		this->entities.emplace_back(i + 1);
	}

	this->countChanged(this->rowCount());
}
