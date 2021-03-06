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
    void testVehicleSpeedChanged();
    void testVehicleSpeedUnchanged();

private:
    Machine *m_machine;
    EngineTwin *m_engine;
    MainModel *m_model;
};

void TestMainModel::init()
{
//    m_machine = createMachine(Machine::Configuration::Mock);
//    m_model = new MainModel{};
//    connect(m_machine->engine(), &EngineTwin::engineSpeedChanged,
//            m_model, &MainModel::setEngineSpeed);
//    connect(m_machine->engine(), &EngineTwin::vehicleSpeedChanged,
//            m_model, &MainModel::setVehicleSpeed);
}

void TestMainModel::cleanup()
{
//    delete m_model;
//    delete m_machine;
}

void TestMainModel::testEngineSpeed()
{
//    QSignalSpy spy{m_model, &MainModel::engineSpeedChanged};
//    Quantity rpm{Quantity::Id::EngineSpeed, 930.0};
//    emit m_machine->engine()->engineSpeedChanged(rpm);
//    QCOMPARE(m_model->engineSpeed()->quantity(), rpm);
//    QCOMPARE(spy.count(), 1);
}

void TestMainModel::testVehicleSpeedChanged()
{
//    QSignalSpy spy{m_model, &MainModel::vehicleSpeedChanged};
//    Quantity xKph{Quantity::Id::VehicleSpeed, 7.2};
//    emit m_machine->engine()->vehicleSpeedChanged(xKph);
//    auto kph = m_model->vehicleSpeed()->quantity();
//    QCOMPARE(kph.value(), xKph.value());
//    QCOMPARE(spy.count(), 1);
}

void TestMainModel::testVehicleSpeedUnchanged()
{
//    QSignalSpy spy{m_model, &MainModel::vehicleSpeedChanged};
//    Quantity xKph{Quantity::Id::VehicleSpeed, 7.2};
//    m_model->setVehicleSpeed(xKph);
//    spy.clear();

//    emit m_machine->engine()->vehicleSpeedChanged(xKph);
//    auto kph = m_model->vehicleSpeed()->quantity();
//    QCOMPARE(kph.value(), xKph.value());
//    QCOMPARE(spy.count(), 0);

}

QTEST_GUILESS_MAIN(TestMainModel)

#include "test_main_model.moc"
