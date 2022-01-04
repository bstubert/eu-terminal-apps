// Copyright, Burkhard Stubert (burkhard.stubert@embeddeduse.com)

#include <memory>

#include <QtDebug>
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

signals:
    void errorMessage(const QString &message);

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
        switch (quantity.id())
        {
        case Quantity::Id::EngineSpeed:
            updateEngineSpeed(quantity);
            break;
        case Quantity::Id::VehicleSpeed:
            updateVehicleSpeed(quantity);
            break;
        default:
            auto message = QString{"EngineTwin received unknown quantity ID: %1"}
                    .arg(static_cast<quint32>(quantity.id()), 0, 16);
            emit errorMessage(message);
            qWarning() << message;
            break;
        }
    }
}

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
    connect(router, &CanBusRouter::newEngineQuantities,
            m_impl.get(), &Impl::updateQuantities);
    connect(m_impl.get(), &Impl::errorMessage,
            this, &EngineTwin::errorMessage);
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
