// Copyright, Burkhard Stubert (burkhard.stubert@embeddeduse.com)

#include <QList>
#include <QSignalSpy>
#include <QtTest>

#include "engine_twin.h"
#include "private/can_bus_router.h"
#include "private/quantity.h"

class TestEngineTwin : public QObject
{
    Q_OBJECT

private slots:
    void init();
    void cleanup();
    void testEngineSpeed();
    void testVehicleSpeed();
    void testUnknownQuantity();
    void testQuantityWithOffset_data();
    void testQuantityWithOffset();

signals:
    void newEngineQuantities(const QList<Quantity> &quantityColl);

private:
    CanBusRouter *m_router;
    EngineTwin *m_engine;
};

void TestEngineTwin::init()
{
    m_router = new CanBusRouter{nullptr};
    m_engine = new EngineTwin{m_router};
}

void TestEngineTwin::cleanup()
{
    delete m_engine;
    delete m_router;
}

void TestEngineTwin::testEngineSpeed()
{
    QSignalSpy spy{m_engine, &EngineTwin::errorMessage};
    Quantity q{Quantity::Id::EngineSpeed, QByteArray::fromHex("101d")};
    emit m_router->newEngineQuantities({q});
    QCOMPARE(m_engine->engineSpeed()->value(), 930.0);
    QCOMPARE(spy.count(), 0);
}

void TestEngineTwin::testVehicleSpeed()
{
    QSignalSpy spy{m_engine, &EngineTwin::errorMessage};
    Quantity q{Quantity::Id::VehicleSpeed, QByteArray::fromHex("8006")};
    emit m_router->newEngineQuantities({q});
    QCOMPARE(m_engine->vehicleSpeed()->value(), 6.5);
    QCOMPARE(spy.count(), 0);
}

void TestEngineTwin::testUnknownQuantity()
{
    QSignalSpy spy{m_engine, &EngineTwin::errorMessage};
    Quantity q{Quantity::Id(0xffffffff), QByteArray::fromHex("1234")};
    emit m_router->newEngineQuantities({q});
    QCOMPARE(spy.count(), 1);
}

void TestEngineTwin::testQuantityWithOffset_data()
{
    QTest::addColumn<QByteArray>("hexValue");
    QTest::addColumn<qreal>("value");

    QTest::addRow("value = +89") << QByteArray::fromHex("d6") << 89.0;
    QTest::addRow("value = -14") << QByteArray::fromHex("6f") << -14.0;
    QTest::addRow("value = 0") << QByteArray::fromHex("7d") << 0.0;
}

void TestEngineTwin::testQuantityWithOffset()
{
    QFETCH(QByteArray, hexValue);
    QFETCH(qreal, value);

    Quantity q{Quantity::Id::ActualEnginePercentTorque, hexValue};
    emit m_router->newEngineQuantities({q});
    QCOMPARE(m_engine->actualEnginePercentTorque()->value(), value);
}

QTEST_GUILESS_MAIN(TestEngineTwin)

#include "test_engine_twin.moc"
