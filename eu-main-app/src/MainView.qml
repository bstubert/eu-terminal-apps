// Copyright, Burkhard Stubert (burkhard.stubert@embeddeduse.com)

import QtQuick

Rectangle
{
    property real rpm: mainModel.engineSpeed.value

    color: "#1800a3" // duke blue

    Text
    {
        id: rpmText
        width: 160
        height: 56
        text: Number(mainModel.engineSpeed.value).toFixed(0)
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
        text: mainModel.engineSpeed.unit
        color: "#ebf5ee"
        font.pixelSize: 24
    }
}
