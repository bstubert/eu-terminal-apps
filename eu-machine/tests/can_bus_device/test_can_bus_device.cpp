// Copyright, Burkhard Stubert (burkhard.stubert@embeddeduse.com)

#include <QSignalSpy>
#include <QtTest>

#include "mock_can_bus_device.h"

class TestCanBusDevice : public QObject
{
    Q_OBJECT

    const QCanBusFrame frame1{1U, QByteArray{8, 1}};
    const QCanBusFrame frame2{2U, QByteArray{8, 2}};

private slots:
    void testConnectAndDisconnectDevice();

    void testConnectionFailed_data();
    void testConnectionFailed();

    void testDisconnectDevice_data();
    void testDisconnectDevice();

    void testWriteFrame();
    void testWriteNoFrameWhenNotConnected();
    void testWriteFrameFails();
    void testWritingInvalidFrameFails();

    void testReadFramesOneByOne();
    void testReadAllFrames();
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
    device.connectDevice();
    QVERIFY(device.writeFrame(QCanBusFrame{}));
    auto frames = device.recordedFrames();
    QCOMPARE(frames.count(), 1);
    QCOMPARE(spy.count(), frames.count());
    QCOMPARE(frames[0].toString(), QCanBusFrame{}.toString());
}

void TestCanBusDevice::testWriteNoFrameWhenNotConnected()
{
    MockCanBusDevice device;
    QSignalSpy spy{&device, &QCanBusDevice::framesWritten};
    QVERIFY(!device.writeFrame(QCanBusFrame{}));
    auto frames = device.recordedFrames();
    QCOMPARE(frames.count(), 0);
    QCOMPARE(spy.count(), frames.count());
}

void TestCanBusDevice::testWriteFrameFails()
{
    MockCanBusDevice device;
    QSignalSpy spy{&device, &QCanBusDevice::framesWritten};
    device.connectDevice();
    device.setWriteSucceeded(false);
    QVERIFY(!device.writeFrame(QCanBusFrame{}));
    QCOMPARE(device.error(), QCanBusDevice::WriteError);
    auto frames = device.recordedFrames();
    QCOMPARE(frames.count(), 0);
    QCOMPARE(spy.count(), frames.count());
}

void TestCanBusDevice::testWritingInvalidFrameFails()
{
    MockCanBusDevice device;
    QSignalSpy spy{&device, &QCanBusDevice::framesWritten};
    device.connectDevice();
    QVERIFY(!device.writeFrame(QCanBusFrame{QCanBusFrame::InvalidFrame}));
    QCOMPARE(device.error(), QCanBusDevice::WriteError);
    auto frames = device.recordedFrames();
    QCOMPARE(frames.count(), 0);
    QCOMPARE(spy.count(), frames.count());
}

void TestCanBusDevice::testReadFramesOneByOne()
{
    MockCanBusDevice device;
    QSignalSpy spy{&device, &QCanBusDevice::framesReceived};
    device.connectDevice();
    device.receiveFrames({frame1, frame2});
    QCOMPARE(spy.count(), 1);

    QCOMPARE(device.framesAvailable(), 2);
    auto frame = device.readFrame();
    QCOMPARE(frame.toString(), frame1.toString());

    QCOMPARE(device.framesAvailable(), 1);
    frame = device.readFrame();
    QCOMPARE(frame.toString(), frame2.toString());

    QCOMPARE(device.framesAvailable(), 0);
}

void TestCanBusDevice::testReadAllFrames()
{
    MockCanBusDevice device;
    QSignalSpy spy{&device, &QCanBusDevice::framesReceived};
    device.connectDevice();
    device.receiveFrames({frame1, frame2});
    QCOMPARE(spy.count(), 1);

    QCOMPARE(device.framesAvailable(), 2);
    auto frames = device.readAllFrames();
    QCOMPARE(frames[0].toString(), frame1.toString());
    QCOMPARE(frames[1].toString(), frame2.toString());
    QCOMPARE(device.framesAvailable(), 0);
}

QTEST_GUILESS_MAIN(TestCanBusDevice)

#include "test_can_bus_device.moc"
