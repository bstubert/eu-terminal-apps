// Copyright, Burkhard Stubert (burkhard.stubert@embeddeduse.com)

#pragma once

#include <QCanBusDevice>
#include <QList>
#include <QObject>

#include "quantity.h"

class CanBusRouter : public QObject
{
    Q_OBJECT
public:
    explicit CanBusRouter(QCanBusDevice *canBus, QObject *parent = nullptr);
    virtual ~CanBusRouter();

signals:
    void updatedEngineQuantities(const QList<Quantity> &quantityColl);

private slots:
    void onFramesReceived();

private:
    QCanBusDevice *m_canBus;
};
