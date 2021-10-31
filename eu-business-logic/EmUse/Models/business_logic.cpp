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

// NOTE: We cannot move the connections to main(), because this function is called by the QML
// item MainView and the MainModel object is deleted by the QML engine.
MainModel *BusinessLogic::mainModel() const
{
    static MainModel *s_mainModel = nullptr;
    if (s_mainModel == nullptr)
    {
        s_mainModel = new MainModel{};
        connect(m_machine->engine(), &EngineTwin::engineSpeed,
                s_mainModel, &MainModel::setEngineSpeed);

    }
    return s_mainModel;
}
