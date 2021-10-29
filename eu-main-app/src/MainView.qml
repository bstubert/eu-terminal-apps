// Copyright, Burkhard Stubert (burkhard.stubert@embeddeduse.com)

import QtQuick

import EmUse.Models

Rectangle
{
    property MainModel model: BusinessLogic.mainModel

    color: "#1800a3" // duke blue

    Text
    {
        id: rpmText
        width: 160
        height: 56
        text: Number(model.engineSpeed.value).toFixed(0)
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
        text: model.engineSpeed.unit
        color: "#ebf5ee"
        font.pixelSize: 24
    }
}
