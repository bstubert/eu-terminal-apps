// Copyright, Burkhard Stubert (burkhard.stubert@embeddeduse.com)

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

signals:
    // TODO: Once available use MockCanBusRouter to emit engineSpeed() signal.
    void engineSpeed(const Quantity &rpm);

private:
    EngineTwin *m_engine;
};

void TestEngineTwin::init()
{
    m_engine = new EngineTwin{};
    connect(this, &TestEngineTwin::engineSpeed,
            m_engine, &EngineTwin::engineSpeed);
}

void TestEngineTwin::cleanup()
{
    delete m_engine;
}

void TestEngineTwin::testEngineSpeed()
{
    QSignalSpy rpmSpy{m_engine, &EngineTwin::engineSpeed};
    emit engineSpeed(Quantity{930.0, u"rpm"_qs});
    QCOMPARE(rpmSpy.count(), 1);
    auto rpm = rpmSpy.first().first().value<Quantity>();
    QCOMPARE(rpm.value(), 930.0);
    QCOMPARE(rpm.unit(), u"rpm"_qs);
}

QTEST_GUILESS_MAIN(TestEngineTwin)

#include "test_engine_twin.moc"
