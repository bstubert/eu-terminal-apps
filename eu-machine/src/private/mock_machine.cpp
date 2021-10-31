// Copyright, Burkhard Stubert (burkhard.stubert@embeddeduse.com)

#include "engine_twin.h"
#include "private/mock_machine.h"

struct MockMachine::Impl
{
    EngineTwin m_engine{};
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
