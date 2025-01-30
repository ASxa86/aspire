#include <aspire/ItemView.h>

using aspire::ItemView;

ItemView::ItemView(QQuickItem* parent) : QQuickItem(parent)
{
	this->setFlag(QQuickItem::Flag::ItemHasContents);
	this->setFlag(QQuickItem::Flag::ItemIsViewport);
	this->setFlag(QQuickItem::Flag::ItemClipsChildrenToShape);
	this->setAcceptedMouseButtons(Qt::MouseButton::AllButtons);
}

void ItemView::setContentItem(QQuickItem* x) noexcept
{
	if(this->contentItem == x)
	{
		return;
	}

	if(this->contentItem != nullptr)
	{
		this->contentItem->setParentItem(nullptr);
	}

	this->contentItem = x;

	if(this->contentItem != nullptr)
	{
		this->contentItem->setParentItem(this);
	}

	this->contentItemChanged(this->contentItem);
}

QQuickItem* ItemView::getContentItem() const noexcept
{
	return this->contentItem;
}

void ItemView::mouseMoveEvent(QMouseEvent* event)
{
	if(this->selectedItem == nullptr || this->grabPos.has_value() == false)
	{
		return;
	}

	// Item position is defined as the top left corner.
	// Sicne we want to move the item at the location we grabbed
	// we need to apply an offset at the point of grabbing.
	const auto globalPos = event->globalPos();

	const auto localPos = this->selectedItem->parentItem()->mapFromGlobal(globalPos);
	this->selectedItem->setPosition(localPos - this->grabPos.value());
}

void ItemView::mousePressEvent(QMouseEvent* event)
{
	if(this->contentItem == nullptr)
	{
		return;
	}

	const auto globalPos = event->globalPos();

	for(auto* child : this->contentItem->childItems())
	{
		const auto itemPos = child->mapFromGlobal(globalPos);

		if(child->contains(itemPos) == true)
		{
			this->selectedItem = child;
			this->grabPos = itemPos;
		}
	}
}

void ItemView::mouseReleaseEvent(QMouseEvent* event)
{
	this->grabPos.reset();
	this->selectedItem = nullptr;
}

void ItemView::wheelEvent(QWheelEvent* event)
{
	if(this->contentItem == nullptr)
	{
		return;
	}

	const auto itemPos = this->contentItem->mapFromGlobal(event->globalPosition());
	const auto localPos = this->mapFromGlobal(event->globalPosition());

	const auto center = QPointF{this->contentItem->width() / 2, this->contentItem->height() / 2};
	const auto pos = this->contentItem->position();

	QPointF moveVector{};

	if(event->angleDelta().y() < 0)
	{
		this->contentItem->setScale(this->contentItem->scale() * 0.9);

		// I need to calculate a position that moves the center toward
		// the mouse position.
		moveVector = localPos - pos - center;
	}

	if(event->angleDelta().y() > 0)
	{
		this->contentItem->setScale(this->contentItem->scale() * 1.1);

		moveVector = pos + center - localPos;
	}

	this->contentItem->setPosition(pos + moveVector * 0.1);
}