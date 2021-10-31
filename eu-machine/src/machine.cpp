// Copyright, Burkhard Stubert (burkhard.stubert@embeddeduse.com)

#include "engine_twin.h"
#include "machine.h"
#include "private/can_bus_simulator.h"

struct Machine::Impl
{
    CanBusSimulator m_simulator{nullptr};
    EngineTwin m_engine{};
};

Machine::Machine()
    : m_impl{new Impl{}}
{
    QObject::connect(&m_impl->m_simulator, &CanBusSimulator::engineSpeed,
                     &m_impl->m_engine, &EngineTwin::engineSpeed);
}

Machine::~Machine()
{
}

EngineTwin *Machine::engine() const
{
    return &m_impl->m_engine;
}
