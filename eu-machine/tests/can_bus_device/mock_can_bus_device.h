// Copyright, Burkhard Stubert (burkhard.stubert@embeddeduse.com)

#pragma once

#include <QCanBusDevice>
#include <QCanBusFrame>
#include <QVector>

class MockCanBusDevice : public QCanBusDevice
{
public:
    void setOpenSucceeded(bool succeeded);
    void setState(QCanBusDevice::CanBusDeviceState state);
    QVector<QCanBusFrame> recordedFrames() const;

    bool writeFrame(const QCanBusFrame &frame) override;
    QString interpretErrorFrame(const QCanBusFrame &errorFrame) override;

protected:
    bool open() override;
    void close() override;

private:
    bool m_openSucceeded{true};
    QVector<QCanBusFrame> m_recordedFrames;
};
