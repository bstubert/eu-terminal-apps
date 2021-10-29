// Copyright, Burkhard Stubert (burkhard.stubert@embeddeduse.com)

#include <QGuiApplication>
#include <QObject>
#include <QQmlApplicationEngine>
#include <QQmlContext>

#include "engine_twin.h"
#include "main_model.h"
#include "machine_coordinator.h"
#include "terminal_core_coordinator.h"
#include "terminal_core_singleton.h"

int main(int argc, char *argv[])
{
    QGuiApplication app(argc, argv);

    MachineCoordinator machineComms;
    TerminalCoreCoordinator terminalCore{&machineComms};
    TerminalCoreSingleton::setInstance(&terminalCore);

    QQmlApplicationEngine appEngine;
    appEngine.load(u"qrc:/main.qml"_qs);

    return app.exec();
}
