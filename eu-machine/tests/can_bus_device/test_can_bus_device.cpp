// Copyright, Burkhard Stubert (burkhard.stubert@embeddeduse.com)

#include <QtTest>

#include "mock_can_bus_device.h"

class TestCanBusDevice : public QObject
{
    Q_OBJECT

private slots:
    void testConnectionSucceeded();
    void testConnectionFailed();
};

void TestCanBusDevice::testConnectionSucceeded()
{
    MockCanBusDevice device;
    QVERIFY(device.connectDevice());
    QCOMPARE(device.state(), QCanBusDevice::ConnectedState);
}

void TestCanBusDevice::testConnectionFailed()
{
    MockCanBusDevice device;
    device.setExpectedConnectionState(QCanBusDevice::UnconnectedState);
    QVERIFY(!device.connectDevice());
    QCOMPARE(device.state(), QCanBusDevice::UnconnectedState);
}

QTEST_GUILESS_MAIN(TestCanBusDevice)

#include "test_can_bus_device.moc"
