// Copyright, Burkhard Stubert (burkhard.stubert@embeddeduse.com)

#include <QtTest>

class TestMainView : public QObject
{
    Q_OBJECT

private slots:
    void init();
    void cleanup();
    void testEngineSpeed();

private:
};

void TestMainView::init()
{
}

void TestMainView::cleanup()
{
}

void TestMainView::testEngineSpeed()
{
    QVERIFY(true);
}

QTEST_GUILESS_MAIN(TestMainView)

#include "test_main_view.moc"
