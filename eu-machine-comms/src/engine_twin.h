// Copyright, Burkhard Stubert (burkhard.stubert@embeddeduse.com)

#pragma once

#include <QObject>

class EngineTwin : public QObject
{
    Q_OBJECT
public:
    explicit EngineTwin(QObject *parent = nullptr);

    /*!
     * May only used for testing to emit the signals from the received messages (e.g., engineSpeed).
     * TODO: Move this function to FakeCanBusRouter and connect FakeCanBusRouter::engineSpeed with
     *   EngineTwin::engineSpeed.
     */
    void processReceivedFrames();

signals:
    void engineSpeed(qreal);
};
