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
    void testDecodeQuantitiesFromFrames_data();
    void testDecodeQuantitiesFromFrames();

private:
    const QCanBusFrame eec1_930{0xCF00400, QByteArray::fromHex("001122101d556677")};
    const QCanBusFrame eec1_1017{0xCF00400, QByteArray::fromHex("001122c81f556677")};
    const QCanBusFrame eec1_89_930{0xCF00400, QByteArray::fromHex("0011d6101d556677")};
    const QCanBusFrame ccvs1_6_5{0x18FEF100, QByteArray::fromHex("0080063344556677")};
    const QCanBusFrame ic1{0x18FEF601, QByteArray::fromHex("0011223344556677")};
    const QCanBusFrame unknownPgn{0x18552200, QByteArray::fromHex("0011223344556677")};
    const QCanBusFrame unknownSourceAddress{0x18FEF177, QByteArray::fromHex("0080063344556677")};
    const QCanBusFrame asc2_3_12{0x18d20000, QByteArray::fromHex("18c3223344556677")};

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

void TestCanBusRouter::testDecodeQuantitiesFromFrames_data()
{
    QTest::addColumn<QList<QCanBusFrame>>("incomingFrames");
    QTest::addColumn<QList<Quantity>>("xQuantities");


    QTest::newRow("0 quantities from 1 frame: Unknown PGN")
            << QList<QCanBusFrame>{unknownPgn}
            << QList<Quantity>{};

    QTest::newRow("0 quantities from 1 frame: Unknown source address")
            << QList<QCanBusFrame>{unknownSourceAddress}
            << QList<Quantity>{};

    QTest::newRow("1 quantity from 1 frame: 6.5 kph")
            << QList<QCanBusFrame>{ccvs1_6_5}
            << QList<Quantity>{
                   Quantity{Quantity::Id::VehicleSpeed, QByteArray::fromHex("8006")},
               };

    QTest::newRow("2 quantities from 1 frame: 89%, 930 rpm")
            << QList<QCanBusFrame>{eec1_89_930}
            << QList<Quantity>{
                   Quantity{Quantity::Id::ActualEnginePercentTorque, QByteArray::fromHex("d6")},
                   Quantity{Quantity::Id::EngineSpeed, QByteArray::fromHex("101d")},
               };

    QTest::newRow("3 quantities from 2 frames: 89%, 930 rpm, 6.5 kph")
            << QList<QCanBusFrame>{eec1_89_930, ccvs1_6_5}
            << QList<Quantity>{
                   Quantity{Quantity::Id::ActualEnginePercentTorque, QByteArray::fromHex("d6")},
                   Quantity{Quantity::Id::EngineSpeed, QByteArray::fromHex("101d")},
                   Quantity{Quantity::Id::VehicleSpeed, QByteArray::fromHex("8006")},
               };

    QTest::newRow("3 bit groups from 1 frame: 2, 1, 3, 12")
            << QList<QCanBusFrame>{asc2_3_12}
            << QList<Quantity>{
                   Quantity{Quantity::Id::KneelingRequestLeftSide, QByteArray::fromHex("02")},
                   Quantity{Quantity::Id::KneelingRequestRightSide, QByteArray::fromHex("01")},
                   Quantity{Quantity::Id::NominalLevelRequestFrontAxle, QByteArray::fromHex("03")},
                   Quantity{Quantity::Id::NominalLevelRequestRearAxle, QByteArray::fromHex("0c")},
               };
}

void TestCanBusRouter::testDecodeQuantitiesFromFrames()
{
    QFETCH(QList<QCanBusFrame>, incomingFrames);
    QFETCH(QList<Quantity>, xQuantities);

    QSignalSpy spy{m_router, &CanBusRouter::newEngineQuantities};
    m_canBus->appendIncomingFrames(incomingFrames);
    QCOMPARE(spy.count(), 1);
    auto quantityColl = spy.first().first().value<QList<Quantity>>();
    QCOMPARE(quantityColl.count(), xQuantities.count());
    for (int i = 0; i < quantityColl.count(); ++i)
    {
        QCOMPARE(quantityColl[i].id(), xQuantities[i].id());
        QCOMPARE(quantityColl[i].rawBytes().toHex(), xQuantities[i].rawBytes().toHex());
    }
}

QTEST_GUILESS_MAIN(TestCanBusRouter)

#include "test_can_bus_router.moc"
