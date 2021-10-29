// Copyright, Burkhard Stubert (burkhard.stubert@embeddeduse.com)

#include <QTimeLine>
#include <QTimer>

#include "can_bus_simulator.h"
#include "quantity.h"

CanBusSimulator::CanBusSimulator(QObject *parent)
    : QObject{parent}
    , m_timeLine{new QTimeLine{10000, this}}
{
    m_timeLine->setUpdateInterval(250);
    m_timeLine->setLoopCount(0);
    connect(m_timeLine, &QTimeLine::valueChanged,
            [this](qreal value)
            {
                emit engineSpeed(Quantity{value * 2200.0, u"rpm"_qs});
            });
    m_timeLine->start();
}

void CanBusSimulator::start()
{
    m_timeLine->start();
}
