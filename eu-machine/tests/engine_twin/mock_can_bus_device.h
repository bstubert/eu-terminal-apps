// Copyright, Burkhard Stubert (burkhard.stubert@embeddeduse.com)

#pragma once

#include <QObject>

class Quantity;

class MockCanBusDevice : public QObject
{
    Q_OBJECT
public:
    explicit MockCanBusDevice(QObject *parent = nullptr);

signals:
    void engineSpeed(const Quantity &rpm);
};
