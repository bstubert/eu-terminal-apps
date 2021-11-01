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
        emit engineSpeed(quantity);
    }
}
