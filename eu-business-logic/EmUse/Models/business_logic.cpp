// Copyright, Burkhard Stubert (burkhard.stubert@embeddeduse.com)

#include "engine_twin.h"
#include "main_model.h"
#include "machine.h"
#include "business_logic.h"
#include "business_logic_singleton.h"


BusinessLogic::BusinessLogic(std::shared_ptr<Machine> machine,
                             QObject *parent)
    : QObject(parent)
    , m_machine{machine}
{
    BusinessLogicSingleton::setInstance(this);

}

BusinessLogic::~BusinessLogic()
{
}


MainModel *BusinessLogic::mainModel()
{
    if (m_mainModel == nullptr)
    {
        m_mainModel = new MainModel{this};
        connect(m_machine->engine(), &EngineTwin::engineSpeed,
                m_mainModel, &MainModel::setEngineSpeed);
        connect(m_machine->engine(), &EngineTwin::vehicleSpeed,
                m_mainModel, &MainModel::setVehicleSpeed);
    }
    return m_mainModel;
}
