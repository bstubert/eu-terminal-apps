// Copyright, Burkhard Stubert (burkhard.stubert@embeddeduse.com)

#include <QSignalSpy>
#include <QtTest>

#include "mock_can_bus_device.h"
//#include "quantity.h"

class TestCanBusDevice : public QObject
{
    Q_OBJECT

private slots:
    void init();
    void cleanup();
    void testEngineSpeed();

private:
    MockCanBusDevice *m_canDevice;
};

void TestCanBusDevice::init()
{
    m_canDevice = new MockCanBusDevice{};
}

void TestCanBusDevice::cleanup()
{
    delete m_canDevice;
}

void TestCanBusDevice::testEngineSpeed()
{
    QVERIFY(true);
}

QTEST_GUILESS_MAIN(TestCanBusDevice)

#include "test_can_bus_device.moc"
