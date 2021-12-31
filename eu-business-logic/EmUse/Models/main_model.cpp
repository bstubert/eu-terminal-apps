// Copyright, Burkhard Stubert (burkhard.stubert@embeddeduse.com)

#include "main_model.h"

MainModel::MainModel(QObject *parent)
    : QObject{parent}
{
}

QuantityObject *MainModel::engineSpeed() const
{
    return m_engineSpeed.get();
}

QuantityObject *MainModel::vehicleSpeed() const
{
    return m_vehicleSpeed.get();
}

void MainModel::setEngineSpeed(std::shared_ptr<QuantityObject> rpm)
{
    m_engineSpeed = rpm;
}

void MainModel::setVehicleSpeed(std::shared_ptr<QuantityObject> kph)
{
    m_vehicleSpeed = kph;
}
