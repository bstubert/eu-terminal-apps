// Copyright, Burkhard Stubert (burkhard.stubert@embeddeduse.com)

#include "engine_twin.h"
#include "main_model.h"
#include "machine.h"
#include "business_logic.h"


BusinessLogic::BusinessLogic(std::shared_ptr<Machine> machine,
                             QObject *parent)
    : QObject(parent)
    , m_machine{machine}
{
}

BusinessLogic::~BusinessLogic()
{
}


MainModel *BusinessLogic::mainModel()
{
    if (m_mainModel == nullptr)
    {
        m_mainModel = new MainModel{this};
        m_mainModel->setEngineSpeed(m_machine->engine()->engineSpeed());
        m_mainModel->setVehicleSpeed(m_machine->engine()->vehicleSpeed());
    }
    return m_mainModel;
}
