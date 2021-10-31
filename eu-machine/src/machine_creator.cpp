// Copyright, Burkhard Stubert (burkhard.stubert@embeddeduse.com)

#include <QtGlobal>

#include "machine_creator.h"
#include "private/simulator_machine.h"

Machine *createMachine(Machine::Configuration configuration)
{
    switch (configuration)
    {
    case Machine::Configuration::Simulator:
        return new SimulatorMachine{};
    default:
        Q_ASSERT_X(false, __PRETTY_FUNCTION__, "Unsupported machine configuration!");
        return nullptr;
    }
}
