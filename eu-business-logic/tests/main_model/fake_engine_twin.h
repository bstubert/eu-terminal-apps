// Copyright, Burkhard Stubert (burkhard.stubert@embeddeduse.com)

#pragma once

#include <QObject>

#include "engine_twin.h"

class FakeEngineTwin : public EngineTwin
{
    Q_OBJECT
public:
    explicit FakeEngineTwin(QObject *parent = nullptr);
};
