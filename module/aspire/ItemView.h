#pragma once

#include <QQuickItem>
#include <aspire/export.hxx>

namespace aspire
{
	class ASPIRE_EXPORT ItemView : public QQuickItem
	{
		Q_OBJECT
		Q_PROPERTY(QQuickItem* contentItem READ getContentItem WRITE setContentItem NOTIFY contentItemChanged)
		QML_ELEMENT

	public:
		explicit ItemView(QQuickItem* parent = nullptr);

		void setContentItem(QQuickItem* x) noexcept;
		QQuickItem* getContentItem() const noexcept;

	signals:
		void contentItemChanged(QQuickItem*);

	private:
		void mouseMoveEvent(QMouseEvent*) override;
		void mousePressEvent(QMouseEvent*) override;
		void mouseReleaseEvent(QMouseEvent*) override;
		void wheelEvent(QWheelEvent*) override;

		QQuickItem* contentItem{};
		QQuickItem* selectedItem{};
		std::optional<QPointF> grabPos;
	};
}