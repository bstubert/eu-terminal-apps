// Copyright, Burkhard Stubert (burkhard.stubert@embeddeduse.com)

#pragma once

#include <QObject>
#include <QString>
#include <QtGlobal>

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
    Quantity(Id id, qreal value, const QString &unit);

    Id id() const;
    qreal value() const;
    QString unit() const;

private:
    Id m_id{Id::Undefined};
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
