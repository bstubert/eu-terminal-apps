// Copyright, Burkhard Stubert (burkhard.stubert@embeddeduse.com)

#include "quantity.h"

Quantity::Quantity()
{
}

Quantity::Quantity(qreal value, const QString &unit)
    : m_value{value}
    , m_unit{unit}
{
}

qreal Quantity::value() const
{
    return m_value;
}

QString Quantity::unit() const
{
    return m_unit;
}