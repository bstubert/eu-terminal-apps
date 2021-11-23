// Copyright, Burkhard Stubert (burkhard.stubert@embeddeduse.com)

#include <memory>

#include <QGuiApplication>
#include <QObject>
#include <QQmlApplicationEngine>
#include <QQmlContext>

#include "machine_creator.h"
#include "business_logic.h"

int main(int argc, char *argv[])
{
    QGuiApplication app(argc, argv);

    std::shared_ptr<Machine> machine{createMachine(Machine::Configuration::Simulator)};
    std::shared_ptr<BusinessLogic> businessLogic{new BusinessLogic{machine}};

    QQmlApplicationEngine appEngine;
    appEngine.rootContext()->setContextProperty("BusinessLogic", businessLogic.get());
    appEngine.load(u"qrc:/main.qml"_qs);

    return app.exec();
}
