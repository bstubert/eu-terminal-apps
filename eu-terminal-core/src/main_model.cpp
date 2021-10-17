// Copyright, Burkhard Stubert (burkhard.stubert@embeddeduse.com)

#include "main_model.h"

MainModel::MainModel(QObject *parent)
    : QObject(parent)
{
}

void MainModel::setEngineSpeed(const Quantity &rpm)
{
    m_engineSpeed = rpm;
}

Quantity MainModel::engineSpeed() const
{
    return m_engineSpeed;
}
