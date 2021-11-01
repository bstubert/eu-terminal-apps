// Copyright, Burkhard Stubert (burkhard.stubert@embeddeduse.com)

#include <QCanBusFrame>
#include <QSignalSpy>
#include <QtTest>

#include "can_bus_router.h"
#include "mock_can_bus_device.h"

class TestCanBusRouter : public QObject
{
    Q_OBJECT

private slots:
    void init();
    void cleanup();
    void testForwardingToEngine();

private:
    const QCanBusFrame eec1{0xCF00400, QByteArray::fromHex("0011223344556677")};

    MockCanBusDevice *m_canBus;
    CanBusRouter *m_router;
};

void TestCanBusRouter::init()
{
    m_canBus = new MockCanBusDevice{};
    m_router = new CanBusRouter{m_canBus};
}

void TestCanBusRouter::cleanup()
{
    delete m_router;
    delete m_canBus;
}

void TestCanBusRouter::testForwardingToEngine()
{
    QSignalSpy spy{m_router, &CanBusRouter::updatedEngineQuantities};
    m_canBus->appendIncomingFrame(eec1);
    QCOMPARE(spy.count(), 1);
    auto quantityColl = spy.first().first().value<QList<Quantity>>();
    QCOMPARE(quantityColl.count(), 1);
    auto quantity = quantityColl.first();
    QCOMPARE(quantity.unit(), u"rpm"_qs);
    QCOMPARE(quantity.value(), 930.0);
}

QTEST_GUILESS_MAIN(TestCanBusRouter)

#include "test_can_bus_router.moc"
