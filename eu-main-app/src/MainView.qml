// Copyright, Burkhard Stubert (burkhard.stubert@embeddeduse.com)

import QtQuick

Rectangle
{
    property alias rpm: rpmValue.text

    color: "#1800a3" // duke blue

    Text
    {
        id: rpmValue
        width: 160
        height: 56
        text: "8830"
        horizontalAlignment: Text.AlignRight
        verticalAlignment: Text.AlignVCenter
        color: "#ebf5ee" // mint cream
        font.pixelSize: 48
    }

    Text
    {
        id: rpmUnit
        anchors.left: rpmValue.right
        anchors.leftMargin: 8
        anchors.baseline: rpmValue.baseline
        text: "rpm"
        color: "#ebf5ee"
        font.pixelSize: 24
    }
}
