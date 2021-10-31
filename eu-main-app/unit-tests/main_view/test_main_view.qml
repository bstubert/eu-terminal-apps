// Copyright, Burkhard Stubert (burkhard.stubert@embeddeduse.com)

import QtQuick
import QtTest

import "../../src"

TestCase
{
    name: "TestMainView"

    MainView
    {
        id: mv
        width: 640
        height: 480
    }

    function test_engine_speed()
    {
        mainModel.setEngineSpeed(930.0);
        compare(mv.rpm, 930.0)
    }
}