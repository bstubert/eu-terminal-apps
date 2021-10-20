// Copyright, Burkhard Stubert (burkhard.stubert@embeddeduse.com)

#pragma once

#include <QObject>
#include <QtGlobal>

#include "quantity_object.h"

class MainModel : public QObject
{
    Q_OBJECT
    Q_PROPERTY(QuantityObject *engineSpeed READ engineSpeed NOTIFY engineSpeedChanged)

public:
    explicit MainModel(QObject *parent = nullptr);

    QuantityObject *engineSpeed() const;

public slots:
    // TODO: Rename into receiveEngineSpeed?
    void setEngineSpeed(const Quantity &rpm);

signals:
    void engineSpeedChanged();

private:
    QuantityObject *m_engineSpeed;
};
