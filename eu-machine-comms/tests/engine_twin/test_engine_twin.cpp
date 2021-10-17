// Copyright, Burkhard Stubert (burkhard.stubert@embeddeduse.com)

#include <QSignalSpy>
#include <QtTest>

#include "engine_twin.h"
#include "fake_can_bus_device.h"
#include "quantity.h"

class TestEngineTwin : public QObject
{
    Q_OBJECT

private slots:
    void init();
    void cleanup();
    void testEngineSpeed();

private:
    FakeCanBusDevice *m_router;
    EngineTwin *m_engine;

};

/*!
 * The composition root of the MachineComms component shall create a CanBusRouter and a EngineTwin
 * object and connect the signals and slots of the two objects properly. This function is an
 * example for the composition root.
 */
void TestEngineTwin::init()
{
    m_router = new FakeCanBusDevice{};
    m_engine = new EngineTwin{};
    connect(m_router, &FakeCanBusDevice::engineSpeed,
            m_engine, &EngineTwin::engineSpeed);
}

void TestEngineTwin::cleanup()
{
    delete m_engine;
    delete m_router;
}

void TestEngineTwin::testEngineSpeed()
{
    QSignalSpy rpmSpy{m_engine, &EngineTwin::engineSpeed};
    m_router->processReceivedFrames();
    QCOMPARE(rpmSpy.count(), 1);
    auto rpm = rpmSpy.first().first().value<Quantity>();
    QCOMPARE(rpm.value(), 930.0);
    QCOMPARE(rpm.unit(), u"rpm"_qs);
}

QTEST_GUILESS_MAIN(TestEngineTwin)

#include "test_engine_twin.moc"