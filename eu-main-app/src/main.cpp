// Copyright, Burkhard Stubert (burkhard.stubert@embeddeduse.com)

#include <QGuiApplication>
#include <QObject>
#include <QQmlApplicationEngine>
#include <QQmlContext>

#include "can_bus_simulator.h"
#include "engine_twin.h"
#include "main_model.h"

int main(int argc, char *argv[])
{
    QGuiApplication app(argc, argv);

    CanBusSimulator simulator;
    EngineTwin engine;
    MainModel mainModel;

    QObject::connect(&simulator, &CanBusSimulator::engineSpeed,
                     &engine, &EngineTwin::engineSpeed);
    QObject::connect(&engine, &EngineTwin::engineSpeed,
                     &mainModel, &MainModel::setEngineSpeed);

    QQmlApplicationEngine appEngine;
    appEngine.rootContext()->setContextProperty(u"mainModel"_qs, &mainModel);
    appEngine.load(u"qrc:/main.qml"_qs);

    simulator.start();

    return app.exec();
}
