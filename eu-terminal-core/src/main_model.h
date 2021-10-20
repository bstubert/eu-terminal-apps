// Copyright, Burkhard Stubert (burkhard.stubert@embeddeduse.com)

#pragma once

#include <QObject>
#include <QtGlobal>

#include "quantity.h"

class MainModel : public QObject
{
    Q_OBJECT
    Q_PROPERTY(Quantity engineSpeed READ engineSpeed NOTIFY engineSpeedChanged)

public:
    explicit MainModel(QObject *parent = nullptr);

    Quantity engineSpeed() const;

public slots:
    // TODO: Rename into receiveEngineSpeed?
    void setEngineSpeed(const Quantity &rpm);

signals:
    void engineSpeedChanged();

private:
    Quantity m_engineSpeed;
};
