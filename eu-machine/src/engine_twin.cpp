// Copyright, Burkhard Stubert (burkhard.stubert@embeddeduse.com)

#include "engine_twin.h"

struct EngineTwin::Impl
{

};

EngineTwin::EngineTwin()
    : m_impl{new Impl{}}
{
}

EngineTwin::~EngineTwin()
{
}

void EngineTwin::updateQuantities(const QList<Quantity> &quantityColl)
{
    for (const auto &quantity : quantityColl)
    {
        if (quantity.id() == Quantity::Id::EngineSpeed)
        {
            emit engineSpeed(quantity);
        }
        else if (quantity.id() == Quantity::Id::VehicleSpeed)
        {
            emit vehicleSpeed(quantity);
        }
    }
}
