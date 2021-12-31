// Copyright, Burkhard Stubert (burkhard.stubert@embeddeduse.com)

#pragma once

#include <QObject>
#include <QQmlEngine>
#include <QtGlobal>

#include "quantity_object.h"

class MainModel : public QObject
{
    Q_OBJECT
    QML_ELEMENT

    Q_PROPERTY(QuantityObject *engineSpeed READ engineSpeed CONSTANT)
    Q_PROPERTY(QuantityObject *vehicleSpeed READ vehicleSpeed CONSTANT)

public:
    explicit MainModel(QObject *parent = nullptr);

    QuantityObject *engineSpeed() const;
    QuantityObject *vehicleSpeed() const;

    void setEngineSpeed(std::shared_ptr<QuantityObject> rpm);
    void setVehicleSpeed(std::shared_ptr<QuantityObject> kph);

private:
    std::shared_ptr<QuantityObject> m_engineSpeed;
    std::shared_ptr<QuantityObject> m_vehicleSpeed;
};
