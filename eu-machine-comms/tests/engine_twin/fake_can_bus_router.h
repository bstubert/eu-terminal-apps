// Copyright, Burkhard Stubert (burkhard.stubert@embeddeduse.com)

#pragma once

#include <QObject>

#include "quantity.h"

class FakeCanBusRouter : public QObject
{
    Q_OBJECT
public:
    explicit FakeCanBusRouter(QObject *parent = nullptr);

    void processReceivedFrames();

signals:
    void engineSpeed(const Quantity &rpm);
};
