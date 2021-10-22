// Copyright, Burkhard Stubert (burkhard.stubert@embeddeduse.com)

#include "terminal_core_singleton.h"

TerminalCoreCoordinator *TerminalCoreSingleton::m_instance = nullptr;

void TerminalCoreSingleton::setInstance(TerminalCoreCoordinator *instance)
{
    m_instance = instance;
}

TerminalCoreCoordinator *TerminalCoreSingleton::create(QQmlEngine *qmlEngine, QJSEngine *jsEngine)
{
    Q_ASSERT(m_instance != nullptr);
    Q_ASSERT(jsEngine->thread() == m_instance->thread());
    QJSEngine::setObjectOwnership(m_instance, QJSEngine::CppOwnership);
    return m_instance;
}
