// Copyright, Burkhard Stubert (burkhard.stubert@embeddeduse.com)

#include <QMap>
#include <QString>

#include "quantity_object.h"

struct QuantityObject::Impl
{
    qreal m_value{0.0};
    QString m_unit;
};

QuantityObject::QuantityObject(const QString &unit, QObject *parent)
    : QObject(parent)
    , m_impl{new Impl{}}
{
    m_impl->m_unit = unit;
}

QuantityObject::~QuantityObject()
{
}

qreal QuantityObject::value() const
{
    return m_impl->m_value;
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
