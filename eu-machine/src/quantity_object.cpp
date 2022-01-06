// Copyright, Burkhard Stubert (burkhard.stubert@embeddeduse.com)

#include <QLocale>
#include <QString>

#include "quantity_object.h"

struct QuantityObject::Impl
{
    qreal m_value{0.0};
    qreal m_minimum{0.0};
    qreal m_maximum{0.0};
    int m_precision{1};
    QString m_unit;
};

QuantityObject::QuantityObject(qreal minimum, qreal maximum,
                               int precision, const QString &unit,
                               QObject *parent)
    : QObject(parent)
    , m_impl{new Impl{}}
{
    m_impl->m_minimum = minimum;
    m_impl->m_maximum = maximum;
    m_impl->m_precision = precision;
    m_impl->m_unit = unit;
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
    QLocale l;
    l.setNumberOptions(QLocale::OmitGroupSeparator);
    return l.toString(value(), 'f', m_impl->m_precision);
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
