// Copyright, Burkhard Stubert (burkhard.stubert@embeddeduse.com)

#include "can_bus_router.h"

class CanBusRouter::Impl
{
};

CanBusRouter::CanBusRouter(QCanBusDevice *canBus, QObject *parent)
    : QObject{parent}
    , m_impl{new Impl{}}
{
}

CanBusRouter::~CanBusRouter()
{
}
