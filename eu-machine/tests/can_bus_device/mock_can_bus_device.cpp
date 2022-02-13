// Copyright, Burkhard Stubert (burkhard.stubert@embeddeduse.com)

#include "mock_can_bus_device.h"


void MockCanBusDevice::setOpenSucceeded(bool succeeded)
{
    m_openSucceeded = succeeded;
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
    if (!m_openSucceeded)
    {
        setError(u"Open failed"_qs, QCanBusDevice::ConnectionError);
        return false;
    }
    setState(QCanBusDevice::ConnectedState);
    return true;
}

void MockCanBusDevice::close()
{
    setState(QCanBusDevice::UnconnectedState);
}
