// Copyright, Burkhard Stubert (burkhard.stubert@embeddeduse.com)

#include <QGuiApplication>
#include <QObject>
#include <QQmlApplicationEngine>
#include <QQmlContext>

#include "machine_creator.h"
#include "business_logic_coordinator.h"

int main(int argc, char *argv[])
{
    QGuiApplication app(argc, argv);

    auto machine = createMachine(Machine::Configuration::Simulator);
    BusinessLogicCoordinator businessLogic{machine};

    QQmlApplicationEngine appEngine;
    appEngine.load(u"qrc:/main.qml"_qs);

    return app.exec();
}
