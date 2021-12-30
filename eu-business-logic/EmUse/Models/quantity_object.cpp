// Copyright, Burkhard Stubert (burkhard.stubert@embeddeduse.com)

#include "quantity.h"
#include "quantity_object.h"

struct QuantityObject::Impl
{
    Quantity m_quantity;
};

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
    return m_impl->m_quantity.unit();
}
