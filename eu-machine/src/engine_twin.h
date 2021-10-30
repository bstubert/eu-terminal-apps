// Copyright, Burkhard Stubert (burkhard.stubert@embeddeduse.com)

#pragma once

#include "abstract_engine_twin.h"

class EngineTwin : public AbstractEngineTwin
{
    Q_OBJECT

public:
    explicit EngineTwin();
    virtual ~EngineTwin();
};
