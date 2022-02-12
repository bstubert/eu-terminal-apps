// Copyright, Burkhard Stubert (burkhard.stubert@embeddeduse.com)

#pragma once

#include <QCanBusDevice>

class MockCanBusDevice : public QCanBusDevice
{
public:
    void setExpectedConnectionState(QCanBusDevice::CanBusDeviceState state);

    bool writeFrame(const QCanBusFrame &frame) override;
    QString interpretErrorFrame(const QCanBusFrame &errorFrame) override;

protected:
    bool open() override;
    void close() override;

private:
    QCanBusDevice::CanBusDeviceState m_expectedConnectionState{QCanBusDevice::ConnectedState};
};
