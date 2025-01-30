#pragma once

#include <QQuickItem>
#include <aspire/export.hxx>

namespace aspire
{
	class ASPIRE_EXPORT ItemView : public QQuickItem
	{
		Q_OBJECT
		Q_PROPERTY(QQuickItem* contentItem READ getContentItem WRITE setContentItem NOTIFY contentItemChanged)
		Q_PROPERTY(double zoom READ getZoom WRITE setZoom NOTIFY zoomChanged)
		QML_ELEMENT

	public:
		explicit ItemView(QQuickItem* parent = nullptr);

		void setContentItem(QQuickItem* x) noexcept;
		QQuickItem* getContentItem() const noexcept;

		void setZoom(double x) noexcept;
		double getZoom() const noexcept;

	signals:
		void contentItemChanged(QQuickItem*);
		void zoomChanged(double);

	private:
		void mouseMoveEvent(QMouseEvent*) override;
		void mousePressEvent(QMouseEvent*) override;
		void mouseReleaseEvent(QMouseEvent*) override;
		void wheelEvent(QWheelEvent*) override;

		QQuickItem* contentItem{};
		QQuickItem* selectedItem{};
		std::optional<QPointF> grabPos;
		double zoom{1.0};
	};
}