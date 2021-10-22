// Copyright, Burkhard Stubert (burkhard.stubert@embeddeduse.com)

import QtQuick

Rectangle
{
    // Causes an error, because QuantityObject is not recognised as a type.
    // Probably fixed by importing a model like TerminalCore.Models
//    property QuantityObject engineSpeed: mainModel.engineSpeed

    property QtObject engineSpeed: mainModel.engineSpeed

    color: "#1800a3" // duke blue

    Text
    {
        id: rpmText
        width: 160
        height: 56
        text: Number(engineSpeed.value).toFixed(0)
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
        text: engineSpeed.unit
        color: "#ebf5ee"
        font.pixelSize: 24
    }
}
