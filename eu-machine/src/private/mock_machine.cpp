// Copyright, Burkhard Stubert (burkhard.stubert@embeddeduse.com)

#include "engine_twin.h"
#include "private/engine_twin_impl.h"
#include "private/mock_machine.h"

struct MockMachine::Impl
{
    EngineTwinImpl m_engineImpl;
    EngineTwin m_engine{&m_engineImpl};
};

MockMachine::MockMachine()
    : Machine{}
    , m_impl{new Impl{}}
{
}

MockMachine::~MockMachine()
{
}

EngineTwin *MockMachine::engine() const
{
    return &m_impl->m_engine;
}
