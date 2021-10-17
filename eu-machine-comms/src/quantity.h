// Copyright, Burkhard Stubert (burkhard.stubert@embeddeduse.com)

#pragma once

#include <QString>
#include <QtGlobal>

class Quantity
{
public:
    Quantity();
    Quantity(qreal value, const QString &unit);

    qreal value() const;
    QString unit() const;

private:
    qreal m_value{0.0};
    QString m_unit;
};

inline bool operator==(const Quantity &q1, const Quantity &q2)
{
    return qFuzzyCompare(q1.value(), q2.value()) && q1.unit() == q2.unit();
}
