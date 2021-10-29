// Copyright, Burkhard Stubert (burkhard.stubert@embeddeduse.com)

#pragma once

#include <QObject>
#include <QQmlEngine>

#include "business_logic_coordinator.h"

class BusinessLogicSingleton
{
    Q_GADGET
    QML_FOREIGN(BusinessLogicCoordinator)
    QML_SINGLETON
    QML_NAMED_ELEMENT(BusinessLogic)

public:
    static void setInstance(BusinessLogicCoordinator *instance);
    static BusinessLogicCoordinator *create(QQmlEngine *qmlEngine, QJSEngine *jsEngine);

private:
    static BusinessLogicCoordinator *m_instance;
};
