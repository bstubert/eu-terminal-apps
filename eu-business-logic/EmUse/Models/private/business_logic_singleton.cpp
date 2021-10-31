// Copyright, Burkhard Stubert (burkhard.stubert@embeddeduse.com)

#include "business_logic_singleton.h"

BusinessLogic *BusinessLogicSingleton::m_instance = nullptr;

void BusinessLogicSingleton::setInstance(BusinessLogic *instance)
{
    m_instance = instance;
}

BusinessLogic *BusinessLogicSingleton::create(QQmlEngine *qmlEngine, QJSEngine *jsEngine)
{
    Q_ASSERT(m_instance != nullptr);
    Q_ASSERT(jsEngine->thread() == m_instance->thread());
    QJSEngine::setObjectOwnership(m_instance, QJSEngine::CppOwnership);
    return m_instance;
}
