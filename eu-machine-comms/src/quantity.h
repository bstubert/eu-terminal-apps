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
