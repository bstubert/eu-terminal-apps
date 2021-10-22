// Copyright, Burkhard Stubert (burkhard.stubert@embeddeduse.com)

#include "engine_twin.h"
#include "machine_comms_coordinator.h"
#include "private/can_bus_simulator.h"

struct MachineCommsCoordinator::Impl
{
    CanBusSimulator m_simulator{nullptr};
    EngineTwin m_engine{nullptr};
};

MachineCommsCoordinator::MachineCommsCoordinator()
    : m_impl{new Impl{}}
{
    QObject::connect(&m_impl->m_simulator, &CanBusSimulator::engineSpeed,
                     &m_impl->m_engine, &EngineTwin::engineSpeed);
}

MachineCommsCoordinator::~MachineCommsCoordinator()
{
}

EngineTwin *MachineCommsCoordinator::engine() const
{
    return &m_impl->m_engine;
}
