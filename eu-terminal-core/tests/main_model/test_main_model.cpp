// Copyright, Burkhard Stubert (burkhard.stubert@embeddeduse.com)

#include <QSignalSpy>
#include <QtTest>

#include "fake_engine_twin.h"
#include "main_model.h"

class TestMainModel : public QObject
{
    Q_OBJECT

private slots:
    void init();
    void cleanup();
    void testEngineSpeed();

private:
    FakeEngineTwin *m_engine;
    MainModel *m_model;
};

void TestMainModel::init()
{
    m_engine = new FakeEngineTwin{};
    m_model = new MainModel{};
    connect(m_engine, &FakeEngineTwin::engineSpeed,
            m_model, &MainModel::setEngineSpeed);
}

void TestMainModel::cleanup()
{
    delete m_model;
    delete m_engine;
}

void TestMainModel::testEngineSpeed()
{
    Quantity rpm{930.0, "rpm"};
    m_engine->emitEngineSpeed(rpm);
    QCOMPARE(m_model->engineSpeed(), rpm);
}

QTEST_GUILESS_MAIN(TestMainModel)

#include "test_main_model.moc"
