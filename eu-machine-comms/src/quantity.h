// Copyright, Burkhard Stubert (burkhard.stubert@embeddeduse.com)

#pragma once

#include <QString>
#include <QtGlobal>

class Quantity
{
public:
    Quantity(qreal value, const QString &unit);

private:
    qreal m_value{0.0};
    QString m_unit;
};
