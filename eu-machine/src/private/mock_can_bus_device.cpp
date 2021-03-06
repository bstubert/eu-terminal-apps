// Copyright, Burkhard Stubert (burkhard.stubert@embeddeduse.com)

#include "mock_can_bus_device.h"
#include "quantity.h"

MockCanBusDevice::MockCanBusDevice(QObject *parent)
    : QCanBusDevice(parent)
{
}

void MockCanBusDevice::appendIncomingFrame(const QCanBusFrame &frame)
{
    appendIncomingFrames({frame});
}

void MockCanBusDevice::appendIncomingFrames(const QList<QCanBusFrame> &frames)
{
    QCanBusDevice::enqueueReceivedFrames(frames);
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
    setState(QCanBusDevice::ConnectedState);
    return true;
}

void MockCanBusDevice::close()
{
    setState(QCanBusDevice::UnconnectedState);
}


