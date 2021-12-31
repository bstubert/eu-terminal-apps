// Copyright, Burkhard Stubert (burkhard.stubert@embeddeduse.com)

#pragma once

#include <QByteArray>
#include <QObject>
#include <QString>
#include <QtGlobal>

// TODO: Rename to J1939SpnValue
class Quantity
{
    Q_GADGET

public:
    enum class Id : quint32
    {
        Undefined = 0U,
        VehicleSpeed = 84U,
        EngineSpeed = 190U,
    };
    Q_ENUM(Id);

    Quantity();
    Quantity(Id id, qreal value, const QByteArray &rawBytes = {});

    Id id() const;
    qreal value() const;
    QByteArray rawBytes() const;

private:
    Id m_id{Id::Undefined};
    qreal m_value{0.0};
    QByteArray m_rawBytes;
};

inline bool operator==(const Quantity &q1, const Quantity &q2)
{
    return q1.id() == q2.id() && qFuzzyCompare(q1.value(), q2.value());
}

inline bool operator!=(const Quantity &q1, const Quantity &q2)
{
    return !(q1 == q2);
}
