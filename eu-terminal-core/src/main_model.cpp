// Copyright, Burkhard Stubert (burkhard.stubert@embeddeduse.com)

#include "main_model.h"

MainModel::MainModel(QObject *parent)
    : QObject(parent)
{
}

void MainModel::setEngineSpeed(const Quantity &rpm)
{
    if (m_engineSpeed != rpm)
    {
        m_engineSpeed = rpm;
        emit engineSpeedChanged();
    }
}

Quantity MainModel::engineSpeed() const
{
    return m_engineSpeed;
}
