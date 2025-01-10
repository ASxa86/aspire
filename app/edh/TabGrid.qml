// Copyright (C) 2017 The Qt Company Ltd.
// SPDX-License-Identifier: LicenseRef-Qt-Commercial OR LGPL-3.0-only OR GPL-2.0-only OR GPL-3.0-only

import QtQuick
import QtQuick.Templates as T
import QtQuick.Controls.Material
import QtQuick.Controls.Material.impl

T.TabBar {
    id: control

    implicitWidth: Math.max(implicitBackgroundWidth + leftInset + rightInset,
                            contentWidth + leftPadding + rightPadding)
    implicitHeight: Math.max(implicitBackgroundHeight + topInset + bottomInset,
                             contentHeight + topPadding + bottomPadding)

    property int rows: 1
    property int columns: 1

    spacing: 1

    contentItem: GridView {
        id: grid

        cellWidth: control.width / control.columns
        cellHeight: control.height / control.rows

        model: control.contentModel
        currentIndex: control.currentIndex

        boundsBehavior: Flickable.StopAtBounds
        flickableDirection: Flickable.AutoFlickIfNeeded
        snapMode: GridView.SnapToRow

        highlightMoveDuration: 250
        highlightFollowsCurrentItem: true
        highlightRangeMode: GridView.ApplyRange
        preferredHighlightBegin: 48
        preferredHighlightEnd: width - 48

        highlight: Item {
            z: 2
            Rectangle {
                height: 2
                width: parent.width
                y: control.position === T.TabBar.Footer ? 0 : parent.height - height
                color: control.Material.accentColor
            }
        }
    }

    background: Rectangle {
        color: control.Material.backgroundColor

        layer.enabled: control.Material.elevation > 0
        layer.effect: ElevationEffect {
            elevation: control.Material.elevation
            fullWidth: true
        }
    }
}
