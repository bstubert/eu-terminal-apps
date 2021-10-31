// Copyright, Burkhard Stubert (burkhard.stubert@embeddeduse.com)

#pragma once

#include <memory>

class EngineTwin;

class Machine
{
public:
    enum class Configuration
    {
        Product,
        Simulator,
        Mock
    };

    Machine();
    Machine(const Machine &) = delete;
    Machine &operator=(const Machine &) = delete;
    ~Machine();

    EngineTwin *engine() const;

private:
    struct Impl;
    std::unique_ptr<Impl> m_impl;
};
