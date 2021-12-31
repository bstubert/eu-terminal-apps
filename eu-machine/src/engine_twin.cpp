// Copyright, Burkhard Stubert (burkhard.stubert@embeddeduse.com)

#include <memory>

#include <QtEndian>

#include "engine_twin.h"
#include "quantity_object.h"

struct EngineTwin::Impl
{
    std::shared_ptr<QuantityObject> m_engineSpeed{new QuantityObject{u"rpm"_qs}};
    std::shared_ptr<QuantityObject> m_vehicleSpeed{new QuantityObject{u"kph"_qs}};
};

EngineTwin::EngineTwin()
    : m_impl{new Impl{}}
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

void EngineTwin::updateQuantities(const QList<Quantity> &quantityColl)
{
    for (const auto &quantity : quantityColl)
    {
        if (quantity.id() == Quantity::Id::EngineSpeed)
        {
            auto rpm = qFromLittleEndian<quint16>(quantity.rawBytes()) / 8.0;
            m_impl->m_engineSpeed->setValue(rpm);
        }
        else if (quantity.id() == Quantity::Id::VehicleSpeed)
        {
            auto kph = qFromLittleEndian<quint16>(quantity.rawBytes()) / 256.0;
            m_impl->m_vehicleSpeed->setValue(kph);
        }
    }
}
