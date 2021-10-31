// Copyright, Burkhard Stubert (burkhard.stubert@embeddeduse.com)

#pragma once

#include <memory>

#include "../machine.h"

class SimulatorMachine : public Machine
{
public:
    SimulatorMachine();
    SimulatorMachine(const SimulatorMachine &) = delete;
    SimulatorMachine &operator=(const SimulatorMachine &) = delete;
    virtual ~SimulatorMachine();

    EngineTwin *engine() const override;

private:
    struct Impl;
    std::unique_ptr<Impl> m_impl;
};
