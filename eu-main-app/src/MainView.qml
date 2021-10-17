// Copyright, Burkhard Stubert (burkhard.stubert@embeddeduse.com)

import QtQuick

Rectangle
{
    property real rpm: 8830.0

    color: "#1800a3" // duke blue

    Text
    {
        id: rpmText
        width: 160
        height: 56
        text: rpm
        horizontalAlignment: Text.AlignRight
        verticalAlignment: Text.AlignVCenter
        color: "#ebf5ee" // mint cream
        font.pixelSize: 48
    }

    Text
    {
        id: rpmUnit
        anchors.left: rpmText.right
        anchors.leftMargin: 8
        anchors.baseline: rpmText.baseline
        text: "rpm"
        color: "#ebf5ee"
        font.pixelSize: 24
    }
}
