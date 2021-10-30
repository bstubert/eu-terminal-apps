// Copyright, Burkhard Stubert (burkhard.stubert@embeddeduse.com)

#pragma once

#include <QObject>

class Quantity;

class FakeCanBusDevice : public QObject
{
    Q_OBJECT
public:
    explicit FakeCanBusDevice(QObject *parent = nullptr);

signals:
    void engineSpeed(const Quantity &rpm);
};
