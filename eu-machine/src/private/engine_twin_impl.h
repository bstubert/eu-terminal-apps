// Copyright, Burkhard Stubert (burkhard.stubert@embeddeduse.com)

#pragma once

#include <memory>

#include <QObject>

#include "quantity.h"
#include "quantity_object.h"

class EngineTwinImpl : public QObject
{
    Q_OBJECT

public slots:
    void updateQuantities(const QList<Quantity> &quantityColl);

public:
    void updateEngineSpeed(const Quantity &quantity);
    void updateVehicleSpeed(const Quantity &quantity);

    // TODO: Pass minimum and maximum to QuantityObject, which also takes care of
    //     bounding the value into the admissible range.
    std::shared_ptr<QuantityObject> m_engineSpeed{new QuantityObject{u"rpm"_qs}};
    std::shared_ptr<QuantityObject> m_vehicleSpeed{new QuantityObject{u"kph"_qs}};
};
