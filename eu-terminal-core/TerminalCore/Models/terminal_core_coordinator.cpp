// Copyright, Burkhard Stubert (burkhard.stubert@embeddeduse.com)

#include "engine_twin.h"
#include "main_model.h"
#include "machine_comms_coordinator.h"
#include "terminal_core_coordinator.h"

TerminalCoreCoordinator::TerminalCoreCoordinator(MachineCommsCoordinator *machineComms,
                                                 QObject *parent)
    : QObject(parent)
    , m_machineComms{machineComms}
{
}

TerminalCoreCoordinator::~TerminalCoreCoordinator()
{
}

MainModel *TerminalCoreCoordinator::mainModel() const
{
    static MainModel *s_mainModel = nullptr;
    if (s_mainModel == nullptr)
    {
        s_mainModel = new MainModel{};
        connect(m_machineComms->engine(), &EngineTwin::engineSpeed,
                s_mainModel, &MainModel::setEngineSpeed);

    }
    return s_mainModel;
}
