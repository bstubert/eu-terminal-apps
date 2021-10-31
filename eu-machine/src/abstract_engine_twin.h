// Copyright, Burkhard Stubert (burkhard.stubert@embeddeduse.com)

#pragma once

#include <QObject>

#include "quantity.h"

class AbstractEngineTwin : public QObject
{
    Q_OBJECT

public:
    virtual ~AbstractEngineTwin() {};

signals:
    /*!
     * When the terminal receives a message with a changed engine speed from the engine ECU,
     * the EngineTwin emits this signal with the engine speed in rpm.
     */
    void engineSpeed(const Quantity &rpm);
};