// Copyright, Burkhard Stubert (burkhard.stubert@embeddeduse.com)

#include "quantity.h"

Quantity::Quantity()
{
}

Quantity::Quantity(Id id, qreal value)
    : m_id{id}
    , m_value{value}
{
}

Quantity::Id Quantity::id() const
{
    return m_id;
}

qreal Quantity::value() const
{
    return m_value;
}
