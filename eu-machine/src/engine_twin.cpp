// Copyright, Burkhard Stubert (burkhard.stubert@embeddeduse.com)

#include <memory>

#include <QtEndian>

#include "engine_twin.h"
#include "private/engine_twin_impl.h"
#include "quantity_object.h"

EngineTwin::EngineTwin(EngineTwinImpl *impl)
    : m_impl{impl}
{
}

EngineTwin::~EngineTwin()
{
}

std::shared_ptr<QuantityObject> EngineTwin::engineSpeed() const
{
    return m_impl->m_engineSpeed;
}

std::shared_ptr<QuantityObject> EngineTwin::vehicleSpeed() const
{
    return m_impl->m_vehicleSpeed;
}

#include "engine_twin.moc"
