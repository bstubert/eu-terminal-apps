// Copyright, Burkhard Stubert (burkhard.stubert@embeddeduse.com)

#include <QGuiApplication>
#include <QObject>
#include <QQmlApplicationEngine>
#include <QQmlContext>

#include "machine_coordinator.h"
#include "business_logic_coordinator.h"
#include "business_logic_singleton.h"

int main(int argc, char *argv[])
{
    QGuiApplication app(argc, argv);

    MachineCoordinator machine;
    BusinessLogicCoordinator businessLogic{&machine};
    BusinessLogicSingleton::setInstance(&businessLogic);

    QQmlApplicationEngine appEngine;
    appEngine.load(u"qrc:/main.qml"_qs);

    return app.exec();
}
