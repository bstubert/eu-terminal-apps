// Copyright, Burkhard Stubert (burkhard.stubert@embeddeduse.com)

#include <memory>

#include <QGuiApplication>
#include <QObject>
#include <QQmlApplicationEngine>
#include <QQmlContext>

#include "machine_creator.h"
#include "business_logic_coordinator.h"

int main(int argc, char *argv[])
{
    QGuiApplication app(argc, argv);

    std::shared_ptr<Machine> machine{createMachine(Machine::Configuration::Simulator)};
    BusinessLogicCoordinator businessLogic{machine};

    QQmlApplicationEngine appEngine;
    appEngine.load(u"qrc:/main.qml"_qs);

    return app.exec();
}
