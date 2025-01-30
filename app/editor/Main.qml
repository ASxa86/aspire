import QtQuick
import QtQuick.Controls
import aspire

Window {
	id: window

	title: "aspire"
	width: 1280
	height: 720
	visible: true
	color: Qt.rgba(0.55, 0.55, 0.55, 1.0)



	SplitView {
		anchors.fill: parent

		Item {
			SplitView.preferredWidth: window.width * 0.25
		}

		ItemView {
			SplitView.preferredWidth: window.width * 0.5

			contentItem: Rectangle {
				id: rect
				color: "steelblue"
				x: -width / 2
				y: -height / 2
				width: 50000
				height: 50000

				Rectangle {
					color: "red"
					x: rect.width / 2
					y: rect.height / 2
					width: 32
					height: 32
				}

				Rectangle {
					color: "green"
					x: rect.width / 2 - 50
					y: rect.height / 2 + 50
					width: 64
					height: 32
				}
			}
		}

		Item {
			SplitView.preferredWidth: window.width * 0.25
		}
	}
}
