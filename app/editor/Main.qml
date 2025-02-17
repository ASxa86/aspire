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

	Component {
		id: source

		Item {
			Rectangle {
				color: "red"
				x: 50
				y: 50
				width: 32
				height: 32

				Text {
					text: "red"
					color: "white"
					font.pointSize: 12
				}
			}

			Rectangle {
				color: "green"
				x: 120
				y: 120
				width: 64
				height: 32

				Rectangle {
					color: "white"
					height: 16
					width: 16
					radius: 8
					x: 90
				}

				Rectangle {
					color: "white"
					height: 16
					width: 16
					radius: 8
					x: -30
				}
			}
		}
	}

	SplitView {
		anchors.fill: parent

		TreeView {
			SplitView.preferredWidth: window.width * 0.25

			selectionModel: ItemSelectionModel {
			}

			model: ModelTreeItem {
				item: view.item
			}

			delegate: TreeViewDelegate {
			}
		}

		ItemView {
			id: view

			SplitView.preferredWidth: window.width * 0.5

			sourceComponent: source

			Text {
				anchors.left: parent.left
				anchors.right: parent.right
				text: (view.zoom * 100.0).toFixed(1) + "%"
				color: "white"
				font.pointSize: 12

				TapHandler {
					onTapped: {
						view.zoom = 1.0
					}
				}
			}
		}

		Item {
			SplitView.preferredWidth: window.width * 0.25
		}
	}
}
