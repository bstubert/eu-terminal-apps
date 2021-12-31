// Copyright, Burkhard Stubert (burkhard.stubert@embeddeduse.com)

#include "quantity.h"

Quantity::Quantity()
{
}

Quantity::Quantity(Id id, const QByteArray &rawBytes)
    : m_id{id}
    , m_rawBytes{rawBytes}
{
}

Quantity::Id Quantity::id() const
{
    return m_id;
}

QByteArray Quantity::rawBytes() const
{
    return m_rawBytes;
}
