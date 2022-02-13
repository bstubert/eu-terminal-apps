// Copyright, Burkhard Stubert (burkhard.stubert@embeddeduse.com)

#pragma once

#include <QCanBusDevice>

class MockCanBusDevice : public QCanBusDevice
{
public:
    void setOpenSucceeded(bool succeeded);
    void setState(QCanBusDevice::CanBusDeviceState state);

    bool writeFrame(const QCanBusFrame &frame) override;
    QString interpretErrorFrame(const QCanBusFrame &errorFrame) override;

protected:
    bool open() override;
    void close() override;

private:
    bool m_openSucceeded{true};
};
