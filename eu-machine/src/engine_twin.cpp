// Copyright, Burkhard Stubert (burkhard.stubert@embeddeduse.com)

#include "engine_twin.h"

EngineTwin::EngineTwin()
{
}

EngineTwin::~EngineTwin()
{
}

void EngineTwin::updateQuantities(const QList<Quantity> &quantityColl)
{
    for (const auto &quantity : quantityColl)
    {
        if (quantity.unit() == u"rpm"_qs)
        {
            emit engineSpeed(quantity);
        }
        else if (quantity.unit() == u"kph"_qs)
        {
            emit vehicleSpeed(quantity);
        }
    }
}
