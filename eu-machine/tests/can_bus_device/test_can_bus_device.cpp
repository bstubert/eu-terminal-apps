// Copyright, Burkhard Stubert (burkhard.stubert@embeddeduse.com)

#include <QCanBusFrame>
#include <QSignalSpy>
#include <QtTest>

#include "mock_can_bus_device.h"

class TestCanBusDevice : public QObject
{
    Q_OBJECT

private slots:
    void init();
    void cleanup();
    void testReceivingOneFrame();

private:
    const QCanBusFrame eec1{0xCF00400, QByteArray::fromHex("0011223344556677")};
    MockCanBusDevice *m_canDevice;
};

void TestCanBusDevice::init()
{
    m_canDevice = new MockCanBusDevice{};
    QVERIFY(m_canDevice->connectDevice());
    QCOMPARE(m_canDevice->state(), QCanBusDevice::ConnectedState);
}

void TestCanBusDevice::cleanup()
{
    m_canDevice->disconnectDevice();
    QCOMPARE(m_canDevice->state(), QCanBusDevice::UnconnectedState);
    delete m_canDevice;
}

void TestCanBusDevice::testReceivingOneFrame()
{
    QSignalSpy spy{m_canDevice, &MockCanBusDevice::framesReceived};
    m_canDevice->appendIncomingFrame(eec1);
    QCOMPARE(spy.count(), 1);
    auto frames = m_canDevice->readAllFrames();
    QCOMPARE(frames.first().toString(), eec1.toString());
}

QTEST_GUILESS_MAIN(TestCanBusDevice)

#include "test_can_bus_device.moc"
