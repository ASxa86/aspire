#include <aspire/ItemView.h>

#include <algorithm>

using aspire::ItemView;

ItemView::ItemView(QQuickItem* parent) : QQuickItem(parent)
{
	this->setFlag(QQuickItem::Flag::ItemHasContents);
	this->setFlag(QQuickItem::Flag::ItemIsViewport);
	this->setFlag(QQuickItem::Flag::ItemClipsChildrenToShape);
	this->setAcceptedMouseButtons(Qt::MouseButton::AllButtons);

	QObject::connect(this, &ItemView::zoomChanged, this,
					 [this]
					 {
						 if(this->contentItem == nullptr)
						 {
							 return;
						 }

						 this->contentItem->setScale(this->zoom);
					 });
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

void ItemView::setZoom(double x) noexcept
{
	if(qFuzzyCompare(this->zoom, x) == true)
	{
		return;
	}

	this->zoom = x;
	this->zoomChanged(this->zoom);
}

double ItemView::getZoom() const noexcept
{
	return this->zoom;
}

void ItemView::mouseMoveEvent(QMouseEvent* event)
{
	if(this->selectedItem == nullptr || this->grabPos.has_value() == false)
	{
		return;
	}

	// Item position is defined as the top left corner.
	// Since we want to move the item at the location we grabbed
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

	if(event->button() == Qt::MouseButton::LeftButton)
	{
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
	else if(event->button() == Qt::MouseButton::MiddleButton)
	{
		const auto itemPos = this->contentItem->mapFromGlobal(globalPos);

		if(this->contentItem->contains(itemPos) == true)
		{
			this->selectedItem = this->contentItem;
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

	static constexpr std::array zoomTable{
		0.005, 0.0075, 0.009, 0.01,	  0.011, 0.012,	 0.013, 0.014,	0.015, 0.016,  0.017, 0.018,  0.019, 0.02,	0.022, 0.024, 0.026, 0.028,
		0.03,  0.0325, 0.035, 0.0375, 0.04,	 0.0425, 0.045, 0.0475, 0.05,  0.0525, 0.055, 0.0575, 0.06,	 0.065, 0.07,  0.075, 0.08,	 0.085,
		0.09,  0.095,  0.10,  0.15,	  0.20,	 0.25,	 0.30,	0.35,	0.40,  0.45,   0.50,  0.55,	  0.60,	 0.65,	0.70,  0.75,  0.80,	 0.85,
		0.90,  0.95,   1.00,  1.05,	  1.1,	 1.15,	 1.2,	1.25,	1.3,   1.35,   1.4,	  1.45,	  1.5,	 1.55,	1.6,   1.65,  1.7,	 1.75,
		1.8,   1.85,   1.9,	  2.0,	  2.1,	 2.2,	 2.3,	2.4,	2.5,   2.6,	   2.7,	  2.8,	  2.9,	 3.0,	3.2,   3.4,	  3.6,	 3.8,
		3.9,   4.0,	   4.25,  4.5,	  4.75,	 5.0,	 5.33,	5.66,	6.0,   6.33,   6.66,  7.0,	  7.5,	 8.0,	8.5,   9.0,	  9.5,	 10.0,
		11.0,  12.0,   13.0,  14.0,	  15.0,	 16.0,	 17.0,	18.0,	19.0,  20.0,   22.0,  24.0,	  26.0,	 28.0,	30.0,  32.0,  34.0,	 36.0,
		38.0,  40.0,   43.33, 46.66,  50.0,	 53.33,	 56.66, 60.0,	63.33, 66.66,  70.0};

	constexpr auto lastIndex = static_cast<int>(zoomTable.size()) - 1;
	static auto currentZoomIndex = std::distance(std::begin(zoomTable), std::ranges::find(zoomTable, 1.0));
	const auto delta = event->angleDelta().y() / 120.0;
	currentZoomIndex = qBound(0, currentZoomIndex + qRound(delta), lastIndex);
	this->setZoom(zoomTable[currentZoomIndex]);

	if(event->angleDelta().y() < 0)
	{
		// I need to calculate a position that moves the center toward
		// the mouse position.
		moveVector = localPos - pos - center;
	}

	if(event->angleDelta().y() > 0)
	{
		moveVector = pos + center - localPos;
	}

	this->contentItem->setPosition(pos + moveVector * 0.1);
}