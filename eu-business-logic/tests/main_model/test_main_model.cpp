// Copyright, Burkhard Stubert (burkhard.stubert@embeddeduse.com)

#include <QSignalSpy>
#include <QtTest>

#include "engine_twin.h"
#include "main_model.h"
#include "machine_creator.h"

class TestMainModel : public QObject
{
    Q_OBJECT

private slots:
    void init();
    void cleanup();
    void testEngineSpeed();
    void testVehicleSpeed();

private:
    Machine *m_machine;
    EngineTwin *m_engine;
    MainModel *m_model;
};

void TestMainModel::init()
{
    m_machine = createMachine(Machine::Configuration::Mock);
    m_model = new MainModel{};
    connect(m_machine->engine(), &EngineTwin::engineSpeed,
            m_model, &MainModel::setEngineSpeed);
    connect(m_machine->engine(), &EngineTwin::vehicleSpeed,
            m_model, &MainModel::setVehicleSpeed);
}

void TestMainModel::cleanup()
{
    delete m_model;
    delete m_machine;
}

void TestMainModel::testEngineSpeed()
{
    QSignalSpy spy{m_model, &MainModel::engineSpeedChanged};
    Quantity rpm{930.0, "rpm"};
    emit m_machine->engine()->engineSpeed(rpm);
    QCOMPARE(m_model->engineSpeed()->quantity(), rpm);
    QCOMPARE(spy.count(), 1);
}

void TestMainModel::testVehicleSpeed()
{
    QSignalSpy spy{m_model, &MainModel::vehicleSpeedChanged};
    Quantity xKph{7.2, "kph"};
    emit m_machine->engine()->vehicleSpeed(xKph);
    auto kph = m_model->vehicleSpeed()->quantity();
    QCOMPARE(kph.value(), xKph.value());
    QCOMPARE(kph.unit(), xKph.unit());
    QCOMPARE(spy.count(), 1);
}

QTEST_GUILESS_MAIN(TestMainModel)

#include "test_main_model.moc"
