// Copyright, Burkhard Stubert (burkhard.stubert@embeddeduse.com)

#include "engine_twin.h"
#include "machine_coordinator.h"
#include "private/can_bus_simulator.h"

struct MachineCoordinator::Impl
{
    CanBusSimulator m_simulator{nullptr};
    EngineTwin m_engine{nullptr};
};

MachineCoordinator::MachineCoordinator()
    : m_impl{new Impl{}}
{
    QObject::connect(&m_impl->m_simulator, &CanBusSimulator::engineSpeed,
                     &m_impl->m_engine, &EngineTwin::engineSpeed);
}

MachineCoordinator::~MachineCoordinator()
{
}

EngineTwin *MachineCoordinator::engine() const
{
    return &m_impl->m_engine;
}
