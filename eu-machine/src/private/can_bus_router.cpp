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
            switch (frame.frameId())
            {
            case 0xCF00400:
            {
                auto payload = frame.payload();
                auto rpm = qFromLittleEndian<quint16>(payload.data() + 3) / 8.0;
                quantityColl.append(Quantity{Quantity::Id::EngineSpeed, rpm, u"rpm"_qs});
                break;
            }
            case 0x18FEF100:
            {
                auto payload = frame.payload();
                auto kph = qFromLittleEndian<quint16>(payload.data() + 1) / 256.0;
                quantityColl.append(Quantity{Quantity::Id::VehicleSpeed, kph, u"kph"_qs});
                break;
            }
            default:
                break;
            }

        }
    }
    emit newEngineQuantities(quantityColl);
}
