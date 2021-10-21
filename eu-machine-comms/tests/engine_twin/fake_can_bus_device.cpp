// Copyright, Burkhard Stubert (burkhard.stubert@embeddeduse.com)

#include "fake_can_bus_device.h"

FakeCanBusDevice::FakeCanBusDevice(QObject *parent)
    : QObject(parent)
{
}

void FakeCanBusDevice::processReceivedFrames()
{
    emit engineSpeed(Quantity{930.0, u"rpm"_qs});
}

