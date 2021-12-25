// Copyright, Burkhard Stubert (burkhard.stubert@embeddeduse.com)

#pragma once

#include <QByteArray>
#include <QString>
#include <QtGlobal>

class Quantity
{
public:
    enum class Pgn : quint16
    {
        EEC1 = 0xF004U,
        CCVS1 = 0xFEF1U
    };

    enum class SourceAddress : quint8
    {
        Engine = 0x00U
    };

    Quantity();
    Quantity(quint32 frameId, const QByteArray &payload);
    Quantity(Pgn pgn, qreal value, const QString &unit);

    Pgn pgn() const;
    SourceAddress sourceAddress() const;
    qreal value() const;
    QString unit() const;

private:
    Pgn m_pgn;
    SourceAddress m_sourceAddress;
    qreal m_value{0.0};
    QString m_unit;
};

inline bool operator==(const Quantity &q1, const Quantity &q2)
{
    return qFuzzyCompare(q1.value(), q2.value()) && q1.unit() == q2.unit();
}

inline bool operator!=(const Quantity &q1, const Quantity &q2)
{
    return !(q1 == q2);
}
