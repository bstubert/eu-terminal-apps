// Copyright, Burkhard Stubert (burkhard.stubert@embeddeduse.com)

#include <QList>
#include <QSignalSpy>
#include <QtDebug>
#include <QtTest>

#include "quantity_object.h"

class TestQuantityObject : public QObject
{
    Q_OBJECT

private slots:
    void initTestCase_data();
    void testValueBoundaries_data();
    void testValueBoundaries();
    void testQuantityAsString_data();
    void testQuantityAsString();

private:
    QString localizedString(QString s) const;
};

void TestQuantityObject::initTestCase_data()
{
    QTest::addColumn<QLocale>("locale");
    QTest::newRow("en_US") << QLocale{u"en_US"_qs};
    QTest::newRow("de_DE") << QLocale{u"de_DE"_qs};
}

void TestQuantityObject::testValueBoundaries_data()
{
    QTest::addColumn<qreal>("value");
    QTest::addColumn<qreal>("xValue");

    QTest::addRow("in range") << 13.2 << 13.2;
    QTest::addRow("too big") << 55.7 << 50.0;
    QTest::addRow("too small") << -3.8 << 0.0;
}

void TestQuantityObject::testValueBoundaries()
{
    QFETCH(qreal, value);
    QFETCH(qreal, xValue);

    QuantityObject rpm{0.0, 50.0, 1, u"kph"_qs};
    rpm.setValue(value);
    QCOMPARE(rpm.value(), xValue);
}

void TestQuantityObject::testQuantityAsString_data()
{
    QTest::addColumn<qreal>("value");
    QTest::addColumn<int>("precision");
    QTest::addColumn<QString>("xValueString");
    QTest::addColumn<QString>("xUnit");

    QTest::addRow("x: round down") << 13.234 << 0 << u"13"_qs << u"kph"_qs;
    QTest::addRow("x: round up") << 1023.622 << 0 << u"1024"_qs << u"kph"_qs;

    QTest::addRow("x.y: round down") << 13.23 << 1 << u"13.2"_qs << u"kph"_qs;
    QTest::addRow("x.y: round up") << 1023.48 << 1 << u"1023.5"_qs << u"kph"_qs;
    QTest::addRow("x.y: .0 shown") << 5.02 << 1 << u"5.0"_qs << u"kph"_qs;
    QTest::addRow("x.y: too small") << -3.8 << 1 << u"0.0"_qs << u"kph"_qs;
    QTest::addRow("x.y: too big") << 4055.14 << 1 << u"3000.0"_qs << u"kph"_qs;

    QTest::addRow("x.yy: round down") << 13.234 << 2 << u"13.23"_qs << u"kph"_qs;
    QTest::addRow("x.yy: round up") << 23.489 << 2 << u"23.49"_qs << u"kph"_qs;
}

void TestQuantityObject::testQuantityAsString()
{
    QFETCH_GLOBAL(QLocale, locale);
    QFETCH(qreal, value);
    QFETCH(int, precision);
    QFETCH(QString, xValueString);
    QFETCH(QString, xUnit);

    QLocale::setDefault(locale);
    QuantityObject rpm{0.0, 3000.0, precision, u"kph"_qs};
    rpm.setValue(value);
    QCOMPARE(rpm.valueString(), localizedString(xValueString));
    QCOMPARE(rpm.unit(), xUnit);
}

QString TestQuantityObject::localizedString(QString s) const
{
    QLocale l;
    return s.replace(".", l.decimalPoint());
}

QTEST_GUILESS_MAIN(TestQuantityObject)

#include "test_quantity_object.moc"
