// Copyright, Burkhard Stubert (burkhard.stubert@embeddeduse.com)

#include <QGuiApplication>
#include <QObject>
#include <QQmlApplicationEngine>
#include <QQmlContext>

#include "engine_twin.h"
#include "main_model.h"
#include "machine_comms_coordinator.h"

int main(int argc, char *argv[])
{
    QGuiApplication app(argc, argv);

    MachineCommsCoordinator machineComms;
    MainModel mainModel;

    QObject::connect(machineComms.engine(), &EngineTwin::engineSpeed,
                     &mainModel, &MainModel::setEngineSpeed);

    QQmlApplicationEngine appEngine;
    appEngine.rootContext()->setContextProperty(u"mainModel"_qs, &mainModel);
    appEngine.load(u"qrc:/main.qml"_qs);

    return app.exec();
}
