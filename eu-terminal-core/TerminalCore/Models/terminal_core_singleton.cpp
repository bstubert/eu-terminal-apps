// Copyright, Burkhard Stubert (burkhard.stubert@embeddeduse.com)

#include "terminal_core_singleton.h"

BusinessLogicCoordinator *TerminalCoreSingleton::m_instance = nullptr;

void TerminalCoreSingleton::setInstance(BusinessLogicCoordinator *instance)
{
    m_instance = instance;
}

BusinessLogicCoordinator *TerminalCoreSingleton::create(QQmlEngine *qmlEngine, QJSEngine *jsEngine)
{
    Q_ASSERT(m_instance != nullptr);
    Q_ASSERT(jsEngine->thread() == m_instance->thread());
    QJSEngine::setObjectOwnership(m_instance, QJSEngine::CppOwnership);
    return m_instance;
}
