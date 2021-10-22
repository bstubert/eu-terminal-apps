// Copyright, Burkhard Stubert (burkhard.stubert@embeddeduse.com)

#include <QGuiApplication>
#include <QObject>
#include <QQmlApplicationEngine>
#include <QQmlContext>

#include "engine_twin.h"
#include "main_model.h"
#include "machine_comms_coordinator.h"
#include "terminal_core_coordinator.h"

int main(int argc, char *argv[])
{
    QGuiApplication app(argc, argv);

    MachineCommsCoordinator machineComms;
    TerminalCoreCoordinator terminalCore{&machineComms};

    QQmlApplicationEngine appEngine;
    appEngine.rootContext()->setContextProperty(u"mainModel"_qs, terminalCore.mainModel());
    appEngine.load(u"qrc:/main.qml"_qs);

    return app.exec();
}
