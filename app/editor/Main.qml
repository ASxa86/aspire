import QtQuick
import QtQuick.Controls
import QtQuick.Layouts
import QtQuick.Models
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
				item: loader.item
			}

			delegate: TreeViewDelegate {
			}
		}

		ItemView {
			id: view

			SplitView.preferredWidth: window.width * 0.5

			contentItem: Rectangle {
				id: rect
				color: "steelblue"
				x: -center.x
				y: -center.y
				width: (parent.width / 0.005) * 3
				height: (parent.height / 0.005) * 3

				property point center: Qt.point(width / 2, height / 2)

				Rectangle {
					id: vertical
					color: "darkturquoise"
					width: 2 / parent.scale
					height: parent.height
					anchors.centerIn: parent
				}

				Rectangle {
					id: horizontal
					color: "darkturquoise"
					width: parent.width
					height: 2 / parent.scale
					anchors.centerIn: parent
				}

				Rectangle {
					color: "transparent"
					border.color: "darkslategray"
					border.width: 2 / parent.scale
					anchors.left: parent.left
					anchors.leftMargin: parent.center.x
					anchors.top: parent.top
					anchors.topMargin: parent.center.y
					width: 1280
					height: 720

					Loader {
						id: loader
						sourceComponent: source
					}
				}
			}

			Text {
				anchors.left: parent.left
				anchors.right: parent.right
				text: (view.zoom * 100.0).toFixed(1) + "%"
				color: "white"
				font.pointSize: 12
			}
		}

		Item {
			SplitView.preferredWidth: window.width * 0.25
		}
	}
}
