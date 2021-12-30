// Copyright, Burkhard Stubert (burkhard.stubert@embeddeduse.com)

#pragma once

#include <QObject>
#include <QQmlEngine>
#include <QtGlobal>

#include "quantity.h"
#include "quantity_object.h"

class MainModel : public QObject
{
    Q_OBJECT
    QML_ELEMENT

    Q_PROPERTY(QuantityObject *engineSpeed READ engineSpeed NOTIFY engineSpeedChanged)
    Q_PROPERTY(QuantityObject *vehicleSpeed READ vehicleSpeed NOTIFY vehicleSpeedChanged)

public:
    explicit MainModel(QObject *parent = nullptr);

    QuantityObject *engineSpeed() const;
    QuantityObject *vehicleSpeed() const;

public slots:
    void setEngineSpeed(const Quantity &rpm);
    void setVehicleSpeed(const Quantity &kph);

signals:
    void engineSpeedChanged(); 
    void vehicleSpeedChanged();

private:
    QuantityObject *m_engineSpeed;
    QuantityObject *m_vehicleSpeed;
};
