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

    Q_PROPERTY(QuantityObject *engineSpeed READ engineSpeed NOTIFY engineSpeedChanged)

public:
    explicit MainModel(QObject *parent = nullptr);

    QuantityObject *engineSpeed() const;

public slots:
    void setEngineSpeed(const Quantity &rpm);

signals:
    void engineSpeedChanged();

private:
    QuantityObject *m_engineSpeed;
};
