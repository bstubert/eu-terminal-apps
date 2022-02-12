// Copyright, Burkhard Stubert (burkhard.stubert@embeddeduse.com)

#include "mock_can_bus_device.h"

bool MockCanBusDevice::writeFrame(const QCanBusFrame &frame)
{
    return false;
}

QString MockCanBusDevice::interpretErrorFrame(const QCanBusFrame &errorFrame)
{
    return {};
}

bool MockCanBusDevice::open()
{
    return false;
}

void MockCanBusDevice::close()
{
}
