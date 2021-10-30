// Copyright, Burkhard Stubert (burkhard.stubert@embeddeduse.com)

#include "engine_twin.h"
#include "main_model.h"
#include "machine_coordinator.h"
#include "business_logic_coordinator.h"

BusinessLogicCoordinator::BusinessLogicCoordinator(MachineCoordinator *machineComms,
                                                 QObject *parent)
    : QObject(parent)
    , m_machineComms{machineComms}
{
}

BusinessLogicCoordinator::~BusinessLogicCoordinator()
{
}

// NOTE: We cannot move the connections to main(), because this function is called by the QML
// item MainView and the MainModel object is deleted by the QML engine.
MainModel *BusinessLogicCoordinator::mainModel() const
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
