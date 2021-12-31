// Copyright, Burkhard Stubert (burkhard.stubert@embeddeduse.com)

#include <QtEndian>

#include "engine_twin_impl.h"

void EngineTwinImpl::updateQuantities(const QList<Quantity> &quantityColl)
{
    for (const auto &quantity : quantityColl)
    {
        if (quantity.id() == Quantity::Id::EngineSpeed)
        {
            auto rpm = qFromLittleEndian<quint16>(quantity.rawBytes()) / 8.0;
            m_engineSpeed->setValue(rpm);
        }
        else if (quantity.id() == Quantity::Id::VehicleSpeed)
        {
            auto kph = qFromLittleEndian<quint16>(quantity.rawBytes()) / 256.0;
            m_vehicleSpeed->setValue(kph);
        }
    }
}
