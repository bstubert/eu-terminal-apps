// Copyright, Burkhard Stubert (burkhard.stubert@embeddeduse.com)

#include "engine_twin.h"
#include "private/can_bus_simulator.h"
#include "private/simulator_machine.h"

struct SimulatorMachine::Impl
{
    CanBusSimulator m_simulator{nullptr};
    EngineTwin m_engine{};
};

SimulatorMachine::SimulatorMachine()
    : Machine{}
    , m_impl{new Impl{}}
{
    QObject::connect(&m_impl->m_simulator, &CanBusSimulator::engineSpeed,
                     &m_impl->m_engine, &EngineTwin::engineSpeed);
}

SimulatorMachine::~SimulatorMachine()
{
}

EngineTwin *SimulatorMachine::engine() const
{
    return &m_impl->m_engine;
}
