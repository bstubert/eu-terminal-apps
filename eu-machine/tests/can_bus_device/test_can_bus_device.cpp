// Copyright, Burkhard Stubert (burkhard.stubert@embeddeduse.com)

#include <QtTest>

#include "mock_can_bus_device.h"

class TestCanBusDevice : public QObject
{
    Q_OBJECT

private slots:
    void testConnectionSucceeded();
    void testConnectionFailed_data();
    void testConnectionFailed();

    void testDisconnectDevice_data();
    void testDisconnectDevice();
};

// TODO: Introduce data-driven testConnectDevice.
void TestCanBusDevice::testConnectionSucceeded()
{
    MockCanBusDevice device;
    QCOMPARE(device.state(), QCanBusDevice::UnconnectedState);
    QVERIFY(device.connectDevice());
    QCOMPARE(device.state(), QCanBusDevice::ConnectedState);
}

void TestCanBusDevice::testConnectionFailed_data()
{
    QTest::addColumn<QCanBusDevice::CanBusDeviceState>("stateBefore");
    QTest::addColumn<bool>("openSucceeded");
    QTest::addColumn<QCanBusDevice::CanBusDeviceState>("stateAfter");
    QTest::addColumn<QCanBusDevice::CanBusError>("canError");

    QTest::newRow("Unconnected + false -> Unconnected + NoError")
            << QCanBusDevice::UnconnectedState << false
            << QCanBusDevice::UnconnectedState << QCanBusDevice::ConnectionError;
}

void TestCanBusDevice::testConnectionFailed()
{
    QFETCH(QCanBusDevice::CanBusDeviceState, stateBefore);
    QFETCH(bool, openSucceeded);
    QFETCH(QCanBusDevice::CanBusDeviceState, stateAfter);
    QFETCH(QCanBusDevice::CanBusError, canError);

    MockCanBusDevice device;
    device.setState(stateBefore);
    device.setOpenSucceeded(openSucceeded);
    QVERIFY(!device.connectDevice());
    QCOMPARE(device.state(), stateAfter);
    QCOMPARE(device.error(), canError);
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
