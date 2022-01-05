// Copyright, Burkhard Stubert (burkhard.stubert@embeddeduse.com)

#include <QList>
#include <QSignalSpy>
#include <QtTest>

#include "quantity_object.h"

class TestQuantityObject : public QObject
{
    Q_OBJECT

private slots:
    void testVehicleSpeed_data();
    void testVehicleSpeed();
};

void TestQuantityObject::testVehicleSpeed_data()
{
    QTest::addColumn<qreal>("value");
    QTest::addColumn<qreal>("xValue");
    QTest::addColumn<QString>("xUnit");

    QTest::addRow("in range") << 13.2 << 13.2 << u"kph"_qs;
    QTest::addRow("too big") << 55.7 << 50.0 << u"kph"_qs;
    QTest::addRow("too small") << -3.8 << 0.0 << u"kph"_qs;
}

void TestQuantityObject::testVehicleSpeed()
{
    QFETCH(qreal, value);
    QFETCH(qreal, xValue);
    QFETCH(QString, xUnit);

    QuantityObject rpm{u"kph"_qs, 0.0, 50.0};
    rpm.setValue(value);
    QCOMPARE(rpm.value(), xValue);
    QCOMPARE(rpm.unit(), xUnit);
}

QTEST_GUILESS_MAIN(TestQuantityObject)

#include "test_quantity_object.moc"
