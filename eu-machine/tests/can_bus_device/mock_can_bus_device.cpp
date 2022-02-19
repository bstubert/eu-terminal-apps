// Copyright, Burkhard Stubert (burkhard.stubert@embeddeduse.com)

#include "mock_can_bus_device.h"


void MockCanBusDevice::setOpenSucceeded(bool succeeded)
{
    m_openSucceeded = succeeded;
}

void MockCanBusDevice::setWriteSucceeded(bool succeeded)
{
    m_writeSucceeded = succeeded;
}

void MockCanBusDevice::setState(QCanBusDevice::CanBusDeviceState state)
{
    QCanBusDevice::setState(state);
}

QVector<QCanBusFrame> MockCanBusDevice::recordedFrames() const
{
    return m_recordedFrames;
}

bool MockCanBusDevice::writeFrame(const QCanBusFrame &frame)
{
    if (state() != ConnectedState)
    {
        return false;
    }
    if (!m_writeSucceeded)
    {
        setError(u"Writing frame failed"_qs, QCanBusDevice::WriteError);
        return false;
    }
    m_recordedFrames.append(frame);
    emit framesWritten(1);
    return true;
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
