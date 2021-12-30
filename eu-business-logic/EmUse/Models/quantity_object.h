// Copyright, Burkhard Stubert (burkhard.stubert@embeddeduse.com)

#pragma once

#include <QObject>
#include <QQmlEngine>
#include <QString>
#include <QtGlobal>

#include "quantity.h"

class QuantityObject : public QObject
{
    Q_OBJECT
    QML_ELEMENT

    Q_PROPERTY(qreal value READ value NOTIFY quantityChanged)
    Q_PROPERTY(QString unit READ unit CONSTANT)

public:
    explicit QuantityObject(QObject *parent = nullptr);

    const Quantity &quantity() const;
    void setQuantity(const Quantity &quantity);

    qreal value() const;

    QString unit() const;

signals:
    void quantityChanged();

private:
    Quantity m_quantity;
};
