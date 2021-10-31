// Copyright, Burkhard Stubert (burkhard.stubert@embeddeduse.com)

#pragma once

#include <QObject>

#include "main_model.h"

class Machine;

class BusinessLogicCoordinator : public QObject
{
    Q_OBJECT

    Q_PROPERTY(MainModel *mainModel READ mainModel CONSTANT)

public:
    explicit BusinessLogicCoordinator(Machine *machine, QObject *parent = nullptr);
    virtual ~BusinessLogicCoordinator();

    MainModel *mainModel() const;

private:
    Machine *m_machine;
};
