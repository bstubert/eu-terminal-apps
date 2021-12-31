// Copyright, Burkhard Stubert (burkhard.stubert@embeddeduse.com)

#pragma once

#include <memory>

#include <QObject>
#include <QString>
#include <QtGlobal>

class Quantity;

class QuantityObject : public QObject
{
    Q_OBJECT

    Q_PROPERTY(qreal value READ value NOTIFY valueChanged)
    Q_PROPERTY(QString unit READ unit CONSTANT)

public:
    explicit QuantityObject(const QString &unit, QObject *parent = nullptr);
    virtual ~QuantityObject();

    qreal value() const;
    void setValue(qreal value);

    QString unit() const;

signals:
    void valueChanged();

private:
    struct Impl;
    std::unique_ptr<Impl> m_impl;
};
