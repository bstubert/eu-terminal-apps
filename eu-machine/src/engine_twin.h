// Copyright, Burkhard Stubert (burkhard.stubert@embeddeduse.com)

#pragma once

#include <memory>

#include <QList>
#include <QObject>

#include "quantity.h"

class EngineTwin : public QObject
{
    Q_OBJECT

public:
    explicit EngineTwin();
    virtual ~EngineTwin();

public slots:
    /*!
     * Receives a \a quantityColl from the Engine ECU via the CanBusRouter. Emits a signal for each
     * changed quantity (e.g., engineSpeed()).
     */
    void updateQuantities(const QList<Quantity> &quantityColl);

signals:
    /*!
     * When the terminal receives a message with a changed engine speed from the engine ECU,
     * the EngineTwin emits this signal with the engine speed in rpm.
     */
    void engineSpeed(const Quantity &rpm);

    void vehicleSpeed(const Quantity &kph);

private:
    struct Impl;
    std::unique_ptr<Impl> m_impl;
};
