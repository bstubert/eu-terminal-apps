// Copyright, Burkhard Stubert (burkhard.stubert@embeddeduse.com)

#include "fake_engine_twin.h"
#include "quantity.h"

FakeEngineTwin::FakeEngineTwin(QObject *parent)
    : EngineTwin(parent)
{
}

void FakeEngineTwin::emitEngineSpeed(const Quantity &rpm)
{
    emit engineSpeed(rpm);
}
