// Copyright, Burkhard Stubert (burkhard.stubert@embeddeduse.com)

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
            quantityColl.append(Quantity{930.0, u"rpm"_qs});
        }
    }
    emit updatedEngineQuantities(quantityColl);
}
