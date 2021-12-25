// Copyright, Burkhard Stubert (burkhard.stubert@embeddeduse.com)

#include <QtEndian>

#include "can_bus_router.h"

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
        Quantity q{frame.frameId(), frame.payload()};
        if (q.sourceAddress() == Quantity::SourceAddress::Engine)
        {
            quantityColl.append(q);
        }
    }
    emit newEngineQuantities(quantityColl);
}
