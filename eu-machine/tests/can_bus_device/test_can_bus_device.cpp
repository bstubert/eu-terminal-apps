// Copyright, Burkhard Stubert (burkhard.stubert@embeddeduse.com)

#include <QtTest>

class TestCanBusDevice : public QObject
{
    Q_OBJECT

private slots:
    void testCreateCanBusDevice();
};

void TestCanBusDevice::testCreateCanBusDevice()
{
    QVERIFY(true);
}

QTEST_GUILESS_MAIN(TestCanBusDevice)

#include "test_can_bus_device.moc"
