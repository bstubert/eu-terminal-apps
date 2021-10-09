// Copyright, Burkhard Stubert (burkhard.stubert@embeddeduse.com)

#pragma once

#include <QObject>

class EngineTwin : public QObject
{
    Q_OBJECT
public:
    explicit EngineTwin(QObject *parent = nullptr);

signals:
    /*!
     * When the terminal receives a message with a changed engine speed from the engine ECU,
     * the EngineTwin emits this signal with the engine speed in rpm.
     * TODO: Send a Quantity object instead of a qreal, because quanties have a unit, an
     *   admissible value range and more.
     */
    void engineSpeed(qreal rpm);
};
