// Copyright, Burkhard Stubert (burkhard.stubert@embeddeduse.com)

#include "main_model.h"

MainModel::MainModel(QObject *parent)
    : QObject{parent}
    , m_engineSpeed{new QuantityObject{parent}}
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

QuantityObject *MainModel::engineSpeed() const
{
    return m_engineSpeed;
}
