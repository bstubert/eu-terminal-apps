// Copyright, Burkhard Stubert (burkhard.stubert@embeddeduse.com)

#include "main_model.h"

MainModel::MainModel(QObject *parent)
    : QObject{parent}
    , m_engineSpeed{new QuantityObject{parent}}
    , m_vehicleSpeed{new QuantityObject{parent}}
{
}

void MainModel::setEngineSpeed(const Quantity &rpm)
{
    if (m_engineSpeed->quantity() != rpm)
    {
        m_engineSpeed->setQuantity(rpm);
        emit engineSpeedChanged();
    }
}

void MainModel::setVehicleSpeed(const Quantity &kph)
{
    if (m_vehicleSpeed->quantity() != kph)
    {
        m_vehicleSpeed->setQuantity(kph);
        emit vehicleSpeedChanged();
    }
}

QuantityObject *MainModel::engineSpeed() const
{
    return m_engineSpeed;
}

QuantityObject *MainModel::vehicleSpeed() const
{
    return m_vehicleSpeed;
}
