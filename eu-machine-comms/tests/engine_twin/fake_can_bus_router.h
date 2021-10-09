// Copyright, Burkhard Stubert (burkhard.stubert@embeddeduse.com)

#pragma once

#include <QObject>

class FakeCanBusRouter : public QObject
{
    Q_OBJECT
public:
    explicit FakeCanBusRouter(QObject *parent = nullptr);

    void processReceivedFrames();

signals:
    void engineSpeed(qreal rpm);

};
