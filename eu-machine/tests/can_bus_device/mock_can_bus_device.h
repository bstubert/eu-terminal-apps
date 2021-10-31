// Copyright, Burkhard Stubert (burkhard.stubert@embeddeduse.com)

#pragma once

#include <QCanBusDevice>

class Quantity;

class MockCanBusDevice : public QCanBusDevice
{
    Q_OBJECT
public:
    explicit MockCanBusDevice(QObject *parent = nullptr);

signals:
    void engineSpeed(const Quantity &rpm);

public:
    bool writeFrame(const QCanBusFrame &frame) override;
    QString interpretErrorFrame(const QCanBusFrame &errorFrame) override;

protected:
    bool open() override;
    void close() override;
};
