// Copyright, Burkhard Stubert (burkhard.stubert@embeddeduse.com)

#pragma once

#include <memory>

#include <QObject>
#include <QString>
#include <QtGlobal>

class QuantityObject : public QObject
{
    Q_OBJECT

    Q_PROPERTY(qreal value READ value NOTIFY valueChanged)
    Q_PROPERTY(QString valueString READ valueString NOTIFY valueChanged)
    Q_PROPERTY(QString unit READ unit CONSTANT)
    Q_PROPERTY(qreal minimum READ minimum CONSTANT)

public:
    explicit QuantityObject(qreal minimum, qreal maximum,
                            int precision, const QString &unit,
                            QObject *parent = nullptr);
    virtual ~QuantityObject();

    qreal value() const;
    QString valueString() const;
    void setValue(qreal value);

    QString unit() const;

    qreal minimum() const;

signals:
    void valueChanged();

private:
    struct Impl;
    std::unique_ptr<Impl> m_impl;
    qreal m_minimum;
};
