// Copyright, Burkhard Stubert (burkhard.stubert@embeddeduse.com)

#pragma once

#include <QObject>

#include "main_model.h"

class MachineCoordinator;

class BusinessLogicCoordinator : public QObject
{
    Q_OBJECT

    Q_PROPERTY(MainModel *mainModel READ mainModel CONSTANT)

public:
    explicit BusinessLogicCoordinator(MachineCoordinator *machine, QObject *parent = nullptr);
    virtual ~BusinessLogicCoordinator();

    MainModel *mainModel() const;

private:
    MachineCoordinator *m_machine;
};
