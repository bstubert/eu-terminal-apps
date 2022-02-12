// Copyright, Burkhard Stubert (burkhard.stubert@embeddeduse.com)

#include <QtTest>

#include "mock_can_bus_device.h"

class TestCanBusDevice : public QObject
{
    Q_OBJECT

private slots:
    void testCreateCanBusDevice();
};

void TestCanBusDevice::testCreateCanBusDevice()
{
    MockCanBusDevice canBus;
}

QTEST_GUILESS_MAIN(TestCanBusDevice)

#include "test_can_bus_device.moc"
