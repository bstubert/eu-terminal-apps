// Copyright, Burkhard Stubert (burkhard.stubert@embeddeduse.com)

#pragma once

#include <memory.h>

#include <QList>
#include <QObject>

#include "quantity.h"

class QCanBusDevice;

class CanBusRouter : public QObject
{
    Q_OBJECT
public:
    explicit CanBusRouter(QCanBusDevice *canBus, QObject *parent = nullptr);
    virtual ~CanBusRouter();

signals:
    void newEngineQuantities(const QList<Quantity> &quantityColl);

private:
    class Impl;
    std::unique_ptr<Impl> m_impl;
};
