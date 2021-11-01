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
    void testOneFrameForwardedToEngine_data();
    void testOneFrameForwardedToEngine();

private:
    const QCanBusFrame eec1_930{0xCF00400, QByteArray::fromHex("001122101d556677")};
    const QCanBusFrame eec1_1017{0xCF00400, QByteArray::fromHex("001122c81f556677")};
    const QCanBusFrame ic1{0x18FEF601, QByteArray::fromHex("0011223344556677")};

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

void TestCanBusRouter::testOneFrameForwardedToEngine_data()
{
    QTest::addColumn<QList<QCanBusFrame>>("incomingFrames");
    QTest::addColumn<qreal>("rpm");

    QTest::newRow("1 in / 1 out (930 rpm)") << QList<QCanBusFrame>{eec1_930} << 930.0;
    QTest::newRow("1 in / 1 out (1017 rpm)") << QList<QCanBusFrame>{eec1_1017} << 1017.0;
    QTest::newRow("2 in / 1 out (930 rpm)") << QList<QCanBusFrame>{ic1, eec1_930} << 930.0;
}

void TestCanBusRouter::testOneFrameForwardedToEngine()
{
    QFETCH(QList<QCanBusFrame>, incomingFrames);
    QFETCH(qreal, rpm);

    QSignalSpy spy{m_router, &CanBusRouter::updatedEngineQuantities};
    m_canBus->appendIncomingFrames(incomingFrames);
    QCOMPARE(spy.count(), 1);
    auto quantityColl = spy.first().first().value<QList<Quantity>>();
    QCOMPARE(quantityColl.count(), 1);
    auto quantity = quantityColl.first();
    QCOMPARE(quantity.unit(), u"rpm"_qs);
    QCOMPARE(quantity.value(), rpm);
}

QTEST_GUILESS_MAIN(TestCanBusRouter)

#include "test_can_bus_router.moc"
