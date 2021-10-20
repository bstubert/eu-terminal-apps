// Copyright, Burkhard Stubert (burkhard.stubert@embeddeduse.com)

#include "quantity_object.h"

QuantityObject::QuantityObject(QObject *parent)
    : QObject(parent)
{
}

const Quantity &QuantityObject::quantity() const
{
    return m_quantity;
}

void QuantityObject::setQuantity(const Quantity &quantity)
{
    if (m_quantity != quantity)
    {
        m_quantity = quantity;
        emit quantityChanged();
    }
}

qreal QuantityObject::value() const
{
    return m_quantity.value();
}

QString QuantityObject::unit() const
{
    return m_quantity.unit();
}
