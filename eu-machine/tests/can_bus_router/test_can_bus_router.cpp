// Copyright, Burkhard Stubert (burkhard.stubert@embeddeduse.com)

#include <QCanBusFrame>
#include <QSignalSpy>
#include <QtTest>


class TestCanBusRouter : public QObject
{
    Q_OBJECT

private slots:
    void init();
    void cleanup();
    void testReceivingOneFrame();

private:
};

void TestCanBusRouter::init()
{
}

void TestCanBusRouter::cleanup()
{
}

void TestCanBusRouter::testReceivingOneFrame()
{
}

QTEST_GUILESS_MAIN(TestCanBusRouter)

#include "test_can_bus_router.moc"
