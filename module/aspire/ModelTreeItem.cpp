#include <aspire/ModelTreeItem.h>

#include <FactoryComponent.h>
#include <QQuickItem>

using aspire::ModelTreeItem;

ModelTreeItem::ModelTreeItem(QObject* parent) : QStandardItemModel{parent}
{
	QObject::connect(this, &ModelTreeItem::itemChanged, this, &ModelTreeItem::reload);
}

void ModelTreeItem::setItem(QObject* x) noexcept
{
	if(this->item == x)
	{
		return;
	}

	this->item = x;
	this->itemChanged(this->item);
}

QObject* ModelTreeItem::getItem() const noexcept
{
	return this->item;
}

void ModelTreeItem::reload()
{
	this->clear();
	this->insertRow(0, this->load(this->item));
}

QStandardItem* ModelTreeItem::load(QObject* x)
{
	auto* qitem = qobject_cast<QQuickItem*>(x);

	if(qitem == nullptr)
	{
		return nullptr;
	}

	auto* node = new QStandardItem(FactoryComponent::Instance()->findQmlName(qitem->metaObject()).data());

	for(auto* child : qitem->childItems())
	{
		node->appendRow(this->load(child));
	}

	return node;
}