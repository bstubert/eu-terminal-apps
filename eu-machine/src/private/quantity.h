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
        ActualEnginePercentTorque = 513U,
        NominalLevelRequestRearAxle = 1750U,
        NominalLevelRequestFrontAxle = 1751U,
        KneelingRequestRightSide = 1748U,
        KneelingRequestLeftSide = 1749U,
    };
    Q_ENUM(Id);

    Quantity();
    Quantity(Id id, const QByteArray &rawBytes);

    Id id() const;
    QByteArray rawBytes() const;

private:
    Id m_id{Id::Undefined};
    QByteArray m_rawBytes;
};

inline bool operator==(const Quantity &q1, const Quantity &q2)
{
    return q1.id() == q2.id() && q1.rawBytes() == q2.rawBytes();
}

inline bool operator!=(const Quantity &q1, const Quantity &q2)
{
    return !(q1 == q2);
}
