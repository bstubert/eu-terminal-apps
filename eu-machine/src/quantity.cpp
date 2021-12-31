// Copyright, Burkhard Stubert (burkhard.stubert@embeddeduse.com)

#include "quantity.h"

Quantity::Quantity()
{
}

Quantity::Quantity(Id id, qreal value, const QByteArray &rawBytes)
    : m_id{id}
    , m_value{value}
    , m_rawBytes{rawBytes}
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

QByteArray Quantity::rawBytes() const
{
    return m_rawBytes;
}
