// Copyright, Burkhard Stubert (burkhard.stubert@embeddeduse.com)

import QtQuick

import EmUse.Models

Rectangle
{
    property MainModel model: BusinessLogic.mainModel

    color: "#1800a3" // duke blue

    Column
    {
        Row
        {
            spacing: 8

            Text
            {
                id: rpmText
                width: 160
                height: 56
                text: model.engineSpeed.valueString
                horizontalAlignment: Text.AlignRight
                verticalAlignment: Text.AlignVCenter
                color: "#ebf5ee" // mint cream
                font.pixelSize: 48
            }

            Text
            {
                id: rpmUnit
                anchors.baseline: rpmText.baseline
                text: model.engineSpeed.unit
                color: "#ebf5ee"
                font.pixelSize: 24
            }
        }

        Row
        {
            spacing: 8

            Text
            {
                id: kphText
                width: 160
                height: 56
                text: model.vehicleSpeed.valueString
                horizontalAlignment: Text.AlignRight
                verticalAlignment: Text.AlignVCenter
                color: "#ebf5ee" // mint cream
                font.pixelSize: 48
            }

            Text
            {
                anchors.baseline: kphText.baseline
                text: model.vehicleSpeed.unit
                color: "#ebf5ee"
                font.pixelSize: 24
            }
        }
    }
}
