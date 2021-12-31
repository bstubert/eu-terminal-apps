// Copyright, Burkhard Stubert (burkhard.stubert@embeddeduse.com)

#include "can_bus_router.h"
#include "engine_twin.h"
#include "private/can_bus_simulator.h"
#include "private/engine_twin_impl.h"
#include "private/mock_can_bus_device.h"
#include "private/simulator_machine.h"

struct SimulatorMachine::Impl
{
    CanBusSimulator m_simulator{nullptr};
    MockCanBusDevice m_canBus{nullptr};
    CanBusRouter m_router{&m_canBus};
    EngineTwinImpl m_engineImpl;
    EngineTwin m_engine{&m_engineImpl};
};

SimulatorMachine::SimulatorMachine()
    : Machine{}
    , m_impl{new Impl{}}
{
    QObject::connect(&m_impl->m_simulator, &CanBusSimulator::newIncomingFrames,
                     &m_impl->m_canBus, &MockCanBusDevice::appendIncomingFrames);
    QObject::connect(&m_impl->m_router, &CanBusRouter::newEngineQuantities,
                     &m_impl->m_engineImpl, &EngineTwinImpl::updateQuantities);
}

SimulatorMachine::~SimulatorMachine()
{
}

EngineTwin *SimulatorMachine::engine() const
{
    return &m_impl->m_engine;
}
