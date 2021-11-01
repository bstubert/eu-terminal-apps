// Copyright, Burkhard Stubert (burkhard.stubert@embeddeduse.com)

#pragma once

#include <QObject>
#include <QTimeLine>

class Quantity;

class CanBusSimulator : public QObject
{
    Q_OBJECT

public:
    explicit CanBusSimulator(QObject *parent = nullptr);

signals:
    void engineSpeed(const Quantity &rpm);

private:
    QTimeLine m_rpmTimeLine;
};
