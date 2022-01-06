// Copyright, Burkhard Stubert (burkhard.stubert@embeddeduse.com)

#include <QMap>
#include <QString>

#include "quantity_object.h"

struct QuantityObject::Impl
{
    qreal m_value{0.0};
    QString m_unit;
    qreal m_minimum{0.0};
    qreal m_maximum{0.0};
};

QuantityObject::QuantityObject(const QString &unit, qreal minimum, qreal maximum, QObject *parent)
    : QObject(parent)
    , m_impl{new Impl{}}
{
    m_impl->m_unit = unit;
    m_impl->m_minimum = minimum;
    m_impl->m_maximum = maximum;
}

QuantityObject::~QuantityObject()
{
}

qreal QuantityObject::value() const
{
    return qBound(m_impl->m_minimum, m_impl->m_value, m_impl->m_maximum);
}

QString QuantityObject::valueString() const
{
    return QString::number(value(), 'f', 1);
}

void QuantityObject::setValue(qreal value)
{
    m_impl->m_value = value;
    emit valueChanged();
}

QString QuantityObject::unit() const
{
    return m_impl->m_unit;
}
