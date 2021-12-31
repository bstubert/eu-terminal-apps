// Copyright, Burkhard Stubert (burkhard.stubert@embeddeduse.com)

#pragma once

#include <QCanBusFrame>
#include <QObject>
#include <QTimeLine>

class CanBusSimulator : public QObject
{
    Q_OBJECT

public:
    explicit CanBusSimulator(QObject *parent = nullptr);

signals:
    void newIncomingFrames(const QList<QCanBusFrame> &frameColl);

private slots:
    void onEngineSpeedChanged(qreal value);
    void onVehicleSpeedChanged(qreal value);

private:
    QTimeLine m_rpmTimeLine;
    QTimeLine m_kphTimeLine;
};
