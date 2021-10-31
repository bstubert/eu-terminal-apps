// Copyright, Burkhard Stubert (burkhard.stubert@embeddeduse.com)

#pragma once

#include "engine_twin.h"

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
