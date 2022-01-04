// Copyright, Burkhard Stubert (burkhard.stubert@embeddeduse.com)

#pragma once

#include <memory>

#include <QObject>

#include "quantity_object.h"

class CanBusRouter;

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

signals:
    void errorMessage(const QString &message);

private:
    class Impl;
    std::unique_ptr<Impl> m_impl;
};
