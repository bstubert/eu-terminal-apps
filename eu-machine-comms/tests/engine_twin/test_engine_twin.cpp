// Copyright, Burkhard Stubert (burkhard.stubert@embeddeduse.com)

#include <QtTest>

class TestEngineTwin : public QObject
{
    Q_OBJECT

private slots:
    void test1();

};

void TestEngineTwin::test1()
{
}

QTEST_GUILESS_MAIN(TestEngineTwin)

#include "test_engine_twin.moc"
