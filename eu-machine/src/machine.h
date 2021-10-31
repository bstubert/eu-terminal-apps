// Copyright, Burkhard Stubert (burkhard.stubert@embeddeduse.com)

#pragma once

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

    virtual ~Machine();

    virtual EngineTwin *engine() const = 0;
};
