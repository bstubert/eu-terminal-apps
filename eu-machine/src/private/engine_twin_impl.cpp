// Copyright, Burkhard Stubert (burkhard.stubert@embeddeduse.com)

#include <QtEndian>

#include "engine_twin_impl.h"

void EngineTwinImpl::updateQuantities(const QList<Quantity> &quantityColl)
{
    for (const auto &quantity : quantityColl)
    {
        if (quantity.id() == Quantity::Id::EngineSpeed)
        {
            updateEngineSpeed(quantity);
        }
        else if (quantity.id() == Quantity::Id::VehicleSpeed)
        {
            updateVehicleSpeed(quantity);
        }
    }
}

// TODO: Store the update functions in a map and call them depending on Quantity::Id.
//     The update functions could be generated.
void EngineTwinImpl::updateEngineSpeed(const Quantity &quantity)
{
    auto rpm = qFromLittleEndian<quint16>(quantity.rawBytes()) * 0.125;
    m_engineSpeed->setValue(rpm);
}

void EngineTwinImpl::updateVehicleSpeed(const Quantity &quantity)
{
    auto kph = qFromLittleEndian<quint16>(quantity.rawBytes()) * 0.00390625;
    m_vehicleSpeed->setValue(kph);
}
