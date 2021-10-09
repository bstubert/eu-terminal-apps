// Copyright, Burkhard Stubert (burkhard.stubert@embeddeduse.com)

#include "fake_can_bus_router.h"

FakeCanBusRouter::FakeCanBusRouter(QObject *parent)
    : QObject(parent)
{
}

void FakeCanBusRouter::processReceivedFrames()
{
    emit engineSpeed(Quantity{930.0, u"1/min"_qs});
}

