// Copyright, Burkhard Stubert (burkhard.stubert@embeddeduse.com)

#include "quantity.h"

Quantity::Quantity(qreal value, const QString &unit)
    : m_value{value}
    , m_unit{unit}
{
}
