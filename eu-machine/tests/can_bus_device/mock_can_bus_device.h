// Copyright, Burkhard Stubert (burkhard.stubert@embeddeduse.com)

#pragma once

#include <QCanBusDevice>

class MockCanBusDevice : public QCanBusDevice
{
    Q_OBJECT
public:
    explicit MockCanBusDevice(QObject *parent = nullptr);
    void appendIncomingFrame(const QCanBusFrame &frame);

public:
    bool writeFrame(const QCanBusFrame &frame) override;
    QString interpretErrorFrame(const QCanBusFrame &errorFrame) override;

protected:
    bool open() override;
    void close() override;
};
