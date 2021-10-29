// Copyright, Burkhard Stubert (burkhard.stubert@embeddeduse.com)

#include <QGuiApplication>
#include <QObject>
#include <QQmlApplicationEngine>
#include <QQmlContext>

#include "engine_twin.h"
#include "main_model.h"
#include "machine_coordinator.h"
#include "business_logic_coordinator.h"
#include "business_logic_singleton.h"

int main(int argc, char *argv[])
{
    QGuiApplication app(argc, argv);

    MachineCoordinator machineComms;
    BusinessLogicCoordinator terminalCore{&machineComms};
    BusinessLogicSingleton::setInstance(&terminalCore);

    QQmlApplicationEngine appEngine;
    appEngine.load(u"qrc:/main.qml"_qs);

    return app.exec();
}
