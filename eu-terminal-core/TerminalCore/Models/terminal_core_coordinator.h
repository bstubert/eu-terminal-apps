// Copyright, Burkhard Stubert (burkhard.stubert@embeddeduse.com)

#pragma once

#include <QObject>

class MainModel;
class MachineCoordinator;

class TerminalCoreCoordinator : public QObject
{
    Q_OBJECT

    Q_PROPERTY(MainModel *mainModel READ mainModel CONSTANT)

public:
    explicit TerminalCoreCoordinator(MachineCoordinator *machineComms, QObject *parent = nullptr);
    virtual ~TerminalCoreCoordinator();

    MainModel *mainModel() const;

private:
    MachineCoordinator *m_machineComms;
};
