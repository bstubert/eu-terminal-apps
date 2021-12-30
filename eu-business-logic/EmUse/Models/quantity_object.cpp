// Copyright, Burkhard Stubert (burkhard.stubert@embeddeduse.com)

#include <QMap>
#include <QString>

#include "quantity.h"
#include "quantity_object.h"

struct QuantityInfo
{
    QString m_unit;
};

struct QuantityObject::Impl
{
    QString unit() const;
    static const QMap<Quantity::Id, QuantityInfo> m_quantityInfo;
    Quantity m_quantity;
};

const QMap<Quantity::Id, QuantityInfo> QuantityObject::Impl::m_quantityInfo
{
    {Quantity::Id::EngineSpeed, {u"rpm"_qs}},
    {Quantity::Id::VehicleSpeed, {u"kph"_qs}},
};

QString QuantityObject::Impl::unit() const
{
    return m_quantityInfo.value(m_quantity.id()).m_unit;
}



QuantityObject::QuantityObject(QObject *parent)
    : QObject(parent)
    , m_impl{new Impl{}}
{
}

QuantityObject::~QuantityObject()
{
}

const Quantity &QuantityObject::quantity() const
{
    return m_impl->m_quantity;
}

void QuantityObject::setQuantity(const Quantity &quantity)
{
    if (m_impl->m_quantity != quantity)
    {
        m_impl->m_quantity = quantity;
        emit quantityChanged();
    }
}

qreal QuantityObject::value() const
{
    return m_impl->m_quantity.value();
}

QString QuantityObject::unit() const
{
    return m_impl->unit();
}
