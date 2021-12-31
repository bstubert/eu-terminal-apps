// Copyright, Burkhard Stubert (burkhard.stubert@embeddeduse.com)

#pragma once

#include <memory>

#include <QList>
#include <QObject>

#include "quantity.h"
#include "quantity_object.h"

class EngineTwin : public QObject
{
    Q_OBJECT

public:
    explicit EngineTwin();
    virtual ~EngineTwin();

    std::shared_ptr<QuantityObject> engineSpeed() const;
    std::shared_ptr<QuantityObject> vehicleSpeed() const;

public slots:
    /*!
     * Receives a \a quantityColl from the Engine ECU via the CanBusRouter. Emits a signal for each
     * changed quantity (e.g., engineSpeed()).
     */
    void updateQuantities(const QList<Quantity> &quantityColl);

private:
    struct Impl;
    std::unique_ptr<Impl> m_impl;
};
