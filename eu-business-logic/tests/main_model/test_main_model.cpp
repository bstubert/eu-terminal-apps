// Copyright, Burkhard Stubert (burkhard.stubert@embeddeduse.com)

#include <QSignalSpy>
#include <QtTest>

#include "engine_twin.h"
#include "main_model.h"

class TestMainModel : public QObject
{
    Q_OBJECT

private slots:
    void init();
    void cleanup();
    void testEngineSpeed();

private:
    EngineTwin *m_engine;
    MainModel *m_model;
};

void TestMainModel::init()
{
    m_engine = new EngineTwin{};
    m_model = new MainModel{};
    connect(m_engine, &EngineTwin::engineSpeed,
            m_model, &MainModel::setEngineSpeed);
}

void TestMainModel::cleanup()
{
    delete m_model;
    delete m_engine;
}

void TestMainModel::testEngineSpeed()
{
    QSignalSpy spy{m_model, &MainModel::engineSpeedChanged};
    Quantity rpm{930.0, "rpm"};
    emit m_engine->engineSpeed(rpm);
    QCOMPARE(m_model->engineSpeed()->quantity(), rpm);
    QCOMPARE(spy.count(), 1);
}

QTEST_GUILESS_MAIN(TestMainModel)

#include "test_main_model.moc"
