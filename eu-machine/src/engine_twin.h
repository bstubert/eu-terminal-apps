// Copyright, Burkhard Stubert (burkhard.stubert@embeddeduse.com)

#pragma once

#include <memory>

#include <QList>
#include <QObject>

#include "quantity_object.h"

class CanBusRouter;
class EngineTwinImpl;

class EngineTwin : public QObject
{
    Q_OBJECT

public:
    /*!
     * EngineTwin does not take ownership of \a impl.
     */
    explicit EngineTwin(CanBusRouter *router);
    virtual ~EngineTwin();

    std::shared_ptr<QuantityObject> engineSpeed() const;
    std::shared_ptr<QuantityObject> vehicleSpeed() const;

private:
    EngineTwinImpl *m_impl;
};
