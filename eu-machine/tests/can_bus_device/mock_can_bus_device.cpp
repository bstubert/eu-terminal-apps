// Copyright, Burkhard Stubert (burkhard.stubert@embeddeduse.com)

#include "mock_can_bus_device.h"


void MockCanBusDevice::setExpectedConnectionState(QCanBusDevice::CanBusDeviceState state)
{
    m_expectedConnectionState = state;
}

void MockCanBusDevice::setState(QCanBusDevice::CanBusDeviceState state)
{
    QCanBusDevice::setState(state);
}

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
    setState(m_expectedConnectionState);
    return state() == QCanBusDevice::ConnectedState;
}

void MockCanBusDevice::close()
{
    setState(QCanBusDevice::UnconnectedState);
}
