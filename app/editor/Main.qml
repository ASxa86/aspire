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

			source: "file:///D:/dev/aspire/app/editor/Test.qml"

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

			focus: true
			Keys.onPressed: (event) => {
				if (event.key === Qt.Key_S && event.modifiers & Qt.ControlModifier) {
					console.log("Saving...");
					view.save("file:test.qml");
				}
			}
		}

		Item {
			SplitView.preferredWidth: window.width * 0.25
		}
	}
}
