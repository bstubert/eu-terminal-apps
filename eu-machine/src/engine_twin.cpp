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
    std::shared_ptr<QuantityObject> m_engineSpeed{new QuantityObject{u"rpm"_qs, 0.0, 3000.0}};
    std::shared_ptr<QuantityObject> m_vehicleSpeed{new QuantityObject{u"kph"_qs, 0.0, 50.0}};
    std::shared_ptr<QuantityObject> m_actualEnginePercentTorque{
        new QuantityObject{u"%"_qs, 0.0, 100.0}};
};

void EngineTwin::Impl::updateQuantities(const QList<Quantity> &quantityColl)
{
    for (const auto &quantity : quantityColl)
    {
        switch (quantity.id())
        {
        case Quantity::Id::EngineSpeed:
            m_engineSpeed->
                    setValue(qFromLittleEndian<quint16>(quantity.rawBytes()) * 0.125);
            break;
        case Quantity::Id::VehicleSpeed:
            m_vehicleSpeed->
                    setValue(qFromLittleEndian<quint16>(quantity.rawBytes()) * 0.00390625);
            break;
        case Quantity::Id::ActualEnginePercentTorque:
            m_actualEnginePercentTorque->
                    setValue(qFromLittleEndian<quint8>(quantity.rawBytes()) * 1.0 - 125.0);
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

std::shared_ptr<QuantityObject> EngineTwin::actualEnginePercentTorque() const
{
    return m_impl->m_actualEnginePercentTorque;
}

#include "engine_twin.moc"
