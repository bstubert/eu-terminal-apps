// Copyright, Burkhard Stubert (burkhard.stubert@embeddeduse.com)

#include <QList>
#include <QSignalSpy>
#include <QtTest>

#include "quantity_object.h"

class TestQuantityObject : public QObject
{
    Q_OBJECT

private slots:
    void testEngineSpeed();
};

void TestQuantityObject::testEngineSpeed()
{
    QuantityObject rpm{u"rpm"_qs};
    rpm.setValue(13.2);
    QCOMPARE(rpm.value(), 13.2);
    QCOMPARE(rpm.unit(), u"rpm"_qs);
}

QTEST_GUILESS_MAIN(TestQuantityObject)

#include "test_quantity_object.moc"
