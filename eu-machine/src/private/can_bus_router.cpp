// Copyright, Burkhard Stubert (burkhard.stubert@embeddeduse.com)

#include <QtEndian>

#include "can_bus_router.h"

namespace
{
    bool isFrameFromEngine(int frameId)
    {
        return (frameId & 0xff) == 0x00;
    }
}

CanBusRouter::CanBusRouter(QCanBusDevice *canBus, QObject *parent)
    : QObject{parent}
    , m_canBus{canBus}
{
    connect(m_canBus, &QCanBusDevice::framesReceived,
            this, &CanBusRouter::onFramesReceived);
    m_canBus->connectDevice();
}

CanBusRouter::~CanBusRouter()
{
    m_canBus->disconnectDevice();
}

void CanBusRouter::onFramesReceived()
{
    QList<Quantity> quantityColl;
    for (const auto &frame : m_canBus->readAllFrames())
    {
        if (isFrameFromEngine(frame.frameId()))
        {
            auto payload = frame.payload();
            auto rpm = qFromLittleEndian<quint16>(payload.data() + 3) * 0.125;
            quantityColl.append(Quantity{rpm, u"rpm"_qs});
        }
    }
    emit newEngineQuantities(quantityColl);
}
