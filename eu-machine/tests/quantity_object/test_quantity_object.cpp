// Copyright, Burkhard Stubert (burkhard.stubert@embeddeduse.com)

#include <QList>
#include <QSignalSpy>
#include <QtTest>

#include "quantity_object.h"

class TestQuantityObject : public QObject
{
    Q_OBJECT

private slots:
    void testValueBoundaries_data();
    void testValueBoundaries();
    void testQuantityAsString_data();
    void testQuantityAsString();
};

void TestQuantityObject::testValueBoundaries_data()
{
    QTest::addColumn<qreal>("value");
    QTest::addColumn<qreal>("xValue");
    QTest::addColumn<QString>("xUnit");

    QTest::addRow("in range") << 13.2 << 13.2 << u"kph"_qs;
    QTest::addRow("too big") << 55.7 << 50.0 << u"kph"_qs;
    QTest::addRow("too small") << -3.8 << 0.0 << u"kph"_qs;
}

void TestQuantityObject::testValueBoundaries()
{
    QFETCH(qreal, value);
    QFETCH(qreal, xValue);
    QFETCH(QString, xUnit);

    QuantityObject rpm{u"kph"_qs, 0.0, 50.0};
    rpm.setValue(value);
    QCOMPARE(rpm.value(), xValue);
    QCOMPARE(rpm.unit(), xUnit);
}

void TestQuantityObject::testQuantityAsString_data()
{
    QTest::addColumn<qreal>("value");
    QTest::addColumn<QString>("xValueString");
    QTest::addColumn<QString>("xUnit");

    QTest::addRow("round down") << 13.23 << u"13.2"_qs << u"kph"_qs;
    QTest::addRow("round up") << 23.48 << u"23.5"_qs << u"kph"_qs;
    QTest::addRow(".0 shown") << 5.02 << u"5.0"_qs << u"kph"_qs;
    QTest::addRow("too small") << -3.8 << u"0.0"_qs << u"kph"_qs;
    QTest::addRow("too big") << 55.14 << u"50.0"_qs << u"kph"_qs;
}

void TestQuantityObject::testQuantityAsString()
{
    QFETCH(qreal, value);
    QFETCH(QString, xValueString);
    QFETCH(QString, xUnit);

    QuantityObject rpm{u"kph"_qs, 0.0, 50.0};
    rpm.setValue(value);
    QCOMPARE(rpm.valueString(), xValueString);
    QCOMPARE(rpm.unit(), xUnit);
}

QTEST_GUILESS_MAIN(TestQuantityObject)

#include "test_quantity_object.moc"
