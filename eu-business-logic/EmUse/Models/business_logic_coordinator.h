// Copyright, Burkhard Stubert (burkhard.stubert@embeddeduse.com)

#pragma once

#include <memory>

#include <QObject>

#include "main_model.h"

class Machine;

class BusinessLogicCoordinator : public QObject
{
    Q_OBJECT

    Q_PROPERTY(MainModel *mainModel READ mainModel CONSTANT)

public:
    explicit BusinessLogicCoordinator(std::shared_ptr<Machine> machine, QObject *parent = nullptr);
    virtual ~BusinessLogicCoordinator();

    MainModel *mainModel() const;

private:
    std::shared_ptr<Machine> m_machine;
};
