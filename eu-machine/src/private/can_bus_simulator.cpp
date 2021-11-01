// Copyright, Burkhard Stubert (burkhard.stubert@embeddeduse.com)

#include "can_bus_simulator.h"
#include "quantity.h"

CanBusSimulator::CanBusSimulator(QObject *parent)
    : QObject{parent}
    , m_rpmTimeLine{10000, this}
{
    m_rpmTimeLine.setUpdateInterval(250);
    m_rpmTimeLine.setLoopCount(0);
    connect(&m_rpmTimeLine, &QTimeLine::valueChanged,
            [this](qreal value)
            {
                emit engineSpeed(Quantity{value * 2200.0, u"rpm"_qs});
            });
    m_rpmTimeLine.start();
}
