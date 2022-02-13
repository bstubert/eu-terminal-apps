// Copyright, Burkhard Stubert (burkhard.stubert@embeddeduse.com)

#include <QSignalSpy>
#include <QtTest>

#include "mock_can_bus_device.h"

class TestCanBusDevice : public QObject
{
    Q_OBJECT

private slots:
    void testConnectAndDisconnectDevice();

    void testConnectionFailed_data();
    void testConnectionFailed();

    void testDisconnectDevice_data();
    void testDisconnectDevice();

    void testWriteFrame();
};

void TestCanBusDevice::testConnectAndDisconnectDevice()
{
    MockCanBusDevice device;
    QCOMPARE(device.state(), QCanBusDevice::UnconnectedState);

    QVERIFY(device.connectDevice());
    QCOMPARE(device.state(), QCanBusDevice::ConnectedState);

    device.disconnectDevice();
    QCOMPARE(device.state(), QCanBusDevice::UnconnectedState);
}

void TestCanBusDevice::testConnectionFailed_data()
{
    QTest::addColumn<QCanBusDevice::CanBusDeviceState>("stateBefore");
    QTest::addColumn<bool>("openSucceeded");
    QTest::addColumn<QCanBusDevice::CanBusDeviceState>("stateAfter");
    QTest::addColumn<QCanBusDevice::CanBusError>("canError");

    QTest::newRow("Unconnected + false -> Unconnected + ConnectionError")
            << QCanBusDevice::UnconnectedState << false
            << QCanBusDevice::UnconnectedState << QCanBusDevice::ConnectionError;
    QTest::newRow("Connected + true -> Connected + ConnectionError")
            << QCanBusDevice::ConnectedState << true
            << QCanBusDevice::ConnectedState << QCanBusDevice::ConnectionError;
    QTest::newRow("Connecting + false -> Connecting + ConnectionError")
            << QCanBusDevice::ConnectingState << false
            << QCanBusDevice::ConnectingState << QCanBusDevice::ConnectionError;
    QTest::newRow("Closing + true -> Closing + ConnectionError")
            << QCanBusDevice::ClosingState << true
            << QCanBusDevice::ClosingState << QCanBusDevice::ConnectionError;
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

    QTest::newRow("Connecting -> Unconnected")
            << QCanBusDevice::ConnectingState << QCanBusDevice::UnconnectedState;
    QTest::newRow("Closing -> Closing")
            << QCanBusDevice::ClosingState << QCanBusDevice::ClosingState;
    QTest::newRow("Unconnected -> Unconnected")
            << QCanBusDevice::UnconnectedState << QCanBusDevice::UnconnectedState;
}

void TestCanBusDevice::testDisconnectDevice()
{
    QFETCH(QCanBusDevice::CanBusDeviceState, stateBefore);
    QFETCH(QCanBusDevice::CanBusDeviceState, stateAfter);

    MockCanBusDevice device;
    device.setState(stateBefore);
    device.disconnectDevice();
    QCOMPARE(device.state(), stateAfter);
    QCOMPARE(device.error(), QCanBusDevice::NoError);
}

void TestCanBusDevice::testWriteFrame()
{
    MockCanBusDevice device;
    QSignalSpy spy{&device, &QCanBusDevice::framesWritten};
    QVERIFY(device.writeFrame(QCanBusFrame{}));
    QCOMPARE(spy.count(), 1);
}

QTEST_GUILESS_MAIN(TestCanBusDevice)

#include "test_can_bus_device.moc"
