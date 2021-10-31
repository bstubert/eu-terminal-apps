// Copyright, Burkhard Stubert (burkhard.stubert@embeddeduse.com)

#pragma once

#include <memory>

#include "../machine.h"

class MockMachine : public Machine
{
public:
    MockMachine();
    MockMachine(const MockMachine &) = delete;
    MockMachine &operator=(const MockMachine &) = delete;
    virtual ~MockMachine();

    EngineTwin *engine() const override;

private:
    struct Impl;
    std::unique_ptr<Impl> m_impl;
};
