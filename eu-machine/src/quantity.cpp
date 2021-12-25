// Copyright, Burkhard Stubert (burkhard.stubert@embeddeduse.com)

#include <QtEndian>

#include "quantity.h"

namespace
{
qreal toRealValue(Quantity::Pgn pgn, const QByteArray &payload)
{
    switch (pgn)
    {
    case Quantity::Pgn::EEC1:
        return qFromLittleEndian<quint16>(payload.data() + 3) / 8.0;
    case Quantity::Pgn::CCVS1:
        return qFromLittleEndian<quint16>(payload.data() + 1) / 256.0;
    default:
        return 0.0;
    }
}

QString toUnit(Quantity::Pgn pgn)
{
    switch (pgn)
    {
    case Quantity::Pgn::EEC1:
        return u"rpm"_qs;
    case Quantity::Pgn::CCVS1:
        return u"kph"_qs;
    default:
        return {};
    }
}
}

Quantity::Quantity()
{
}

Quantity::Quantity(quint32 frameId, const QByteArray &payload)
    : m_pgn{static_cast<Quantity::Pgn>(frameId >> 8)}
    , m_sourceAddress{static_cast<Quantity::SourceAddress>(frameId & 0xff)}
    , m_value{toRealValue(m_pgn, payload)}
    , m_unit{toUnit(m_pgn)}
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

Quantity::SourceAddress Quantity::sourceAddress() const
{
    return m_sourceAddress;
}

qreal Quantity::value() const
{
    return m_value;
}

QString Quantity::unit() const
{
    return m_unit;
}
