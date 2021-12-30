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
    connect(this, &TestEngineTwin::newEngineQuantities,
            m_engine, &EngineTwin::updateQuantities);
}

void TestEngineTwin::cleanup()
{
    delete m_engine;
}

void TestEngineTwin::testEngineSpeed()
{
    QSignalSpy rpmSpy{m_engine, &EngineTwin::engineSpeed};
    emit newEngineQuantities({Quantity{Quantity::Id::EngineSpeed, 930.0, u"rpm"_qs}});
    QCOMPARE(rpmSpy.count(), 1);
    auto rpm = rpmSpy.first().first().value<Quantity>();
    QCOMPARE(rpm.value(), 930.0);
    QCOMPARE(rpm.unit(), u"rpm"_qs);
}

void TestEngineTwin::testVehicleSpeed()
{
    QSignalSpy spy{m_engine, &EngineTwin::vehicleSpeed};
    emit newEngineQuantities({Quantity{Quantity::Id::VehicleSpeed, 6.5, u"kph"_qs}});
    QCOMPARE(spy.count(), 1);
    auto rpm = spy.first().first().value<Quantity>();
    QCOMPARE(rpm.value(), 6.5);
    QCOMPARE(rpm.unit(), u"kph"_qs);
}

QTEST_GUILESS_MAIN(TestEngineTwin)

#include "test_engine_twin.moc"
