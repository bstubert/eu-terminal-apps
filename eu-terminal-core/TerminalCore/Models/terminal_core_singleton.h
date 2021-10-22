// Copyright, Burkhard Stubert (burkhard.stubert@embeddeduse.com)

#pragma once

#include <QObject>
#include <QQmlEngine>

#include "terminal_core_coordinator.h"

class TerminalCoreSingleton
{
    Q_GADGET
    QML_FOREIGN(TerminalCoreCoordinator)
    QML_SINGLETON
    QML_NAMED_ELEMENT(TerminalCore)

public:
    static void setInstance(TerminalCoreCoordinator *instance);
    static TerminalCoreCoordinator *create(QQmlEngine *qmlEngine, QJSEngine *jsEngine);

private:
    static TerminalCoreCoordinator *m_instance;
};
