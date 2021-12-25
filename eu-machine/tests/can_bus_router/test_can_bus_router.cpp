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
    void testForwardingEngineFrames_data();
    void testForwardingEngineFrames();

private:
    const QCanBusFrame eec1_930{0xCF00400, QByteArray::fromHex("001122101d556677")};
    const QCanBusFrame eec1_1017{0xCF00400, QByteArray::fromHex("001122c81f556677")};
    const QCanBusFrame ccvs1_6_5{0x18FEF100, QByteArray::fromHex("0080063344556677")};
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

void TestCanBusRouter::testForwardingEngineFrames_data()
{
    QTest::addColumn<QList<QCanBusFrame>>("incomingFrames");
    QTest::addColumn<Quantity::Pgn>("pgn");
    QTest::addColumn<qreal>("value");
    QTest::addColumn<QString>("unit");

    QTest::newRow("1 in / 1 out (930 rpm)")
            << QList<QCanBusFrame>{eec1_930}
            << Quantity::Pgn::EEC1 << 930.0 << u"rpm"_qs;
    QTest::newRow("1 in / 1 out (1017 rpm)")
            << QList<QCanBusFrame>{eec1_1017}
            << Quantity::Pgn::EEC1 << 1017.0 << u"rpm"_qs;
    QTest::newRow("2 in / 1 out (930 rpm)")
            << QList<QCanBusFrame>{ic1, eec1_930}
            << Quantity::Pgn::EEC1 << 930.0 << u"rpm"_qs;
    QTest::newRow("1 in / 1 out (6.5 kph)")
            << QList<QCanBusFrame>{ccvs1_6_5}
            << Quantity::Pgn::CCVS1 << 6.5 << u"kph"_qs;
}

void TestCanBusRouter::testForwardingEngineFrames()
{
    QFETCH(QList<QCanBusFrame>, incomingFrames);
    QFETCH(Quantity::Pgn, pgn);
    QFETCH(qreal, value);
    QFETCH(QString, unit);

    QSignalSpy spy{m_router, &CanBusRouter::newEngineQuantities};
    m_canBus->appendIncomingFrames(incomingFrames);
    QCOMPARE(spy.count(), 1);
    auto quantityColl = spy.first().first().value<QList<Quantity>>();
    QCOMPARE(quantityColl.count(), 1);
    auto quantity = quantityColl.first();
    QCOMPARE(quantity.unit(), unit);
    QCOMPARE(quantity.value(), value);
    QCOMPARE(quantity.pgn(), pgn);
}

QTEST_GUILESS_MAIN(TestCanBusRouter)

#include "test_can_bus_router.moc"
