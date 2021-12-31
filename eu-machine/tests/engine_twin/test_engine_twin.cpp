// Copyright, Burkhard Stubert (burkhard.stubert@embeddeduse.com)

#include <QList>
#include <QSignalSpy>
#include <QtTest>

#include "engine_twin.h"
#include "quantity.h"

class TestEngineTwin : public QObject
{
    Q_OBJECT

private slots:
    void init();
    void cleanup();
    void testEngineSpeed();
    void testVehicleSpeed();

signals:
    void newEngineQuantities(const QList<Quantity> &quantityColl);

private:
    EngineTwin *m_engine;
};

void TestEngineTwin::init()
{
    m_engine = new EngineTwin{};
}

void TestEngineTwin::cleanup()
{
    delete m_engine;
}

void TestEngineTwin::testEngineSpeed()
{
    Quantity q{Quantity::Id::EngineSpeed, QByteArray::fromHex("101d")};
    m_engine->updateQuantities({q});
    QCOMPARE(m_engine->engineSpeed()->value(), 930.0);
}

void TestEngineTwin::testVehicleSpeed()
{
    Quantity q{Quantity::Id::VehicleSpeed, QByteArray::fromHex("8006")};
    m_engine->updateQuantities({q});
    QCOMPARE(m_engine->vehicleSpeed()->value(), 6.5);
}

QTEST_GUILESS_MAIN(TestEngineTwin)

#include "test_engine_twin.moc"
