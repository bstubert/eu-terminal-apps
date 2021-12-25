// Copyright, Burkhard Stubert (burkhard.stubert@embeddeduse.com)

#include "quantity.h"

Quantity::Quantity()
{
}

Quantity::Quantity(Pgn pgn, qreal value, const QString &unit)
    : m_pgn{pgn}
    , m_value{value}
    , m_unit{unit}
{
}

Quantity::Pgn Quantity::pgn() const
{
    return m_pgn;
}

qreal Quantity::value() const
{
    return m_value;
}

QString Quantity::unit() const
{
    return m_unit;
}
