import QtQuick
import QtTest

import "../../src"

TestCase
{
    name: "TestMainView"

    MainView
    {
        width: 640
        height: 480
    }

    function test_engine_speed()
    {
        fail("My first QML test is up and running!")
    }
}
