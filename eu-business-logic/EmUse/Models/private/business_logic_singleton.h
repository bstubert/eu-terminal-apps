// Copyright, Burkhard Stubert (burkhard.stubert@embeddeduse.com)

#pragma once

#include <QObject>
#include <QQmlEngine>

#include "business_logic.h"

class BusinessLogicSingleton
{
    Q_GADGET
    QML_FOREIGN(BusinessLogic)
    QML_SINGLETON
    QML_NAMED_ELEMENT(BusinessLogic)

public:
    static void setInstance(BusinessLogic *instance);
    static BusinessLogic *create(QQmlEngine *qmlEngine, QJSEngine *jsEngine);

private:
    static BusinessLogic *m_instance;
};
