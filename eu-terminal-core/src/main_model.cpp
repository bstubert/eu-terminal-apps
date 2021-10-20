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

// TODO: Find a better solution!
void MainModel::setEngineSpeed(qreal rpm)
{
    MainModel::setEngineSpeed(Quantity{rpm, u"rpm"_qs});
}

QuantityObject *MainModel::engineSpeed() const
{
    return m_engineSpeed;
}
