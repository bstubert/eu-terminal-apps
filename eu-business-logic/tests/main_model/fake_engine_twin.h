// Copyright, Burkhard Stubert (burkhard.stubert@embeddeduse.com)

#pragma once

#include "abstract_engine_twin.h"

class FakeEngineTwin : public AbstractEngineTwin
{
    Q_OBJECT
public:
    explicit FakeEngineTwin();
    virtual ~FakeEngineTwin();
};
