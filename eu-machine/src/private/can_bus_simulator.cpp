// Copyright, Burkhard Stubert (burkhard.stubert@embeddeduse.com)

#include <QtEndian>
#include <QtDebug>

#include "can_bus_simulator.h"
#include "quantity.h"

CanBusSimulator::CanBusSimulator(QObject *parent)
    : QObject{parent}
    , m_rpmTimeLine{10000, this}
    , m_kphTimeLine{10000, this}
{
    m_rpmTimeLine.setUpdateInterval(250);
    m_rpmTimeLine.setLoopCount(0);
    connect(&m_rpmTimeLine, &QTimeLine::valueChanged,
            this, &CanBusSimulator::onEngineSpeedChanged);
    m_rpmTimeLine.start();

    m_kphTimeLine.setUpdateInterval(250);
    m_kphTimeLine.setLoopCount(0);
    connect(&m_kphTimeLine, &QTimeLine::valueChanged,
            this, &CanBusSimulator::onVehicleSpeedChanged);
    m_kphTimeLine.start();
}

void CanBusSimulator::onEngineSpeedChanged(qreal value)
{
    QByteArray payload(8, 0);
    qToLittleEndian<quint16>(static_cast<quint16>(qRound(value * 24000.0)), payload.data() + 3);
    emit newIncomingFrames({QCanBusFrame{0xCF00400, payload}});
}

void CanBusSimulator::onVehicleSpeedChanged(qreal value)
{
    QByteArray payload(8, 0);
    qToLittleEndian<quint16>(static_cast<quint16>(qRound(value * 10240.0)), payload.data() + 1);
    emit newIncomingFrames({QCanBusFrame{0x18FEF100, payload}});
}
