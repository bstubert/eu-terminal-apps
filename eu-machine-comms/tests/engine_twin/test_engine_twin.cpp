// Copyright, Burkhard Stubert (burkhard.stubert@embeddeduse.com)

#include <QSignalSpy>
#include <QtTest>

#include "engine_twin.h"

class TestEngineTwin : public QObject
{
    Q_OBJECT

private slots:
    void testEngineSpeed();

};

void TestEngineTwin::testEngineSpeed()
{
    EngineTwin engine;
    QSignalSpy rpmSpy{&engine, &EngineTwin::engineSpeed};
    engine.processReceivedFrames();
    QCOMPARE(rpmSpy.count(), 1);
}

QTEST_GUILESS_MAIN(TestEngineTwin)

#include "test_engine_twin.moc"
