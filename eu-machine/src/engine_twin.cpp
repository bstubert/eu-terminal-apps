// Copyright, Burkhard Stubert (burkhard.stubert@embeddeduse.com)

#include <memory>

#include <QtEndian>

#include "engine_twin.h"
#include "private/can_bus_router.h"
#include "private/quantity.h"
#include "quantity_object.h"

class EngineTwin::Impl : public QObject
{
    Q_OBJECT

public slots:
    void updateQuantities(const QList<Quantity> &quantityColl);

public:
    void updateEngineSpeed(const Quantity &quantity);
    void updateVehicleSpeed(const Quantity &quantity);

    // TODO: Pass minimum and maximum to QuantityObject, which also takes care of
    //     bounding the value into the admissible range.
    std::shared_ptr<QuantityObject> m_engineSpeed{new QuantityObject{u"rpm"_qs}};
    std::shared_ptr<QuantityObject> m_vehicleSpeed{new QuantityObject{u"kph"_qs}};
};

void EngineTwin::Impl::updateQuantities(const QList<Quantity> &quantityColl)
{
    for (const auto &quantity : quantityColl)
    {
        if (quantity.id() == Quantity::Id::EngineSpeed)
        {
            updateEngineSpeed(quantity);
        }
        else if (quantity.id() == Quantity::Id::VehicleSpeed)
        {
            updateVehicleSpeed(quantity);
        }
    }
}

// TODO: Store the update functions in a map and call them depending on Quantity::Id.
//     The update functions could be generated.
void EngineTwin::Impl::updateEngineSpeed(const Quantity &quantity)
{
    auto rpm = qFromLittleEndian<quint16>(quantity.rawBytes()) * 0.125;
    m_engineSpeed->setValue(rpm);
}

void EngineTwin::Impl::updateVehicleSpeed(const Quantity &quantity)
{
    auto kph = qFromLittleEndian<quint16>(quantity.rawBytes()) * 0.00390625;
    m_vehicleSpeed->setValue(kph);
}



EngineTwin::EngineTwin(CanBusRouter *router)
    : m_impl{new Impl{}}
{
    QObject::connect(router, &CanBusRouter::newEngineQuantities,
                     m_impl.get(), &Impl::updateQuantities);

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
