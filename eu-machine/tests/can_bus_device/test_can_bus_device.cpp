// Copyright, Burkhard Stubert (burkhard.stubert@embeddeduse.com)

#include <QtTest>

#include "mock_can_bus_device.h"

class TestCanBusDevice : public QObject
{
    Q_OBJECT

private slots:
    void testConnectionSucceeded();
    void testConnectionFailed();

    void testDisconnectDevice_data();
    void testDisconnectDevice();
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

void TestCanBusDevice::testDisconnectDevice_data()
{
    QTest::addColumn<QCanBusDevice::CanBusDeviceState>("stateBefore");
    QTest::addColumn<QCanBusDevice::CanBusDeviceState>("stateAfter");

    QTest::newRow("Connected -> Unconnected")
            << QCanBusDevice::ConnectedState << QCanBusDevice::UnconnectedState;
    QTest::newRow("Closing -> Closing")
            << QCanBusDevice::ClosingState << QCanBusDevice::ClosingState;
    QTest::newRow("Unconnected -> Unconnected")
            << QCanBusDevice::UnconnectedState << QCanBusDevice::UnconnectedState;
    QTest::newRow("Connecting -> Unconnected")
            << QCanBusDevice::ConnectingState << QCanBusDevice::UnconnectedState;
}

void TestCanBusDevice::testDisconnectDevice()
{
    QFETCH(QCanBusDevice::CanBusDeviceState, stateBefore);
    QFETCH(QCanBusDevice::CanBusDeviceState, stateAfter);

    MockCanBusDevice device;
    device.setState(stateBefore);
    device.disconnectDevice();
    QCOMPARE(device.state(), stateAfter);
}

QTEST_GUILESS_MAIN(TestCanBusDevice)

#include "test_can_bus_device.moc"
