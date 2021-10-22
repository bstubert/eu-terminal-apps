// Copyright, Burkhard Stubert (burkhard.stubert@embeddeduse.com)

#pragma once

#include <QObject>

class MainModel;
class MachineCommsCoordinator;

class TerminalCoreCoordinator : public QObject
{
    Q_OBJECT

    Q_PROPERTY(MainModel *mainModel READ mainModel CONSTANT)

public:
    explicit TerminalCoreCoordinator(MachineCommsCoordinator *machineComms, QObject *parent = nullptr);
    virtual ~TerminalCoreCoordinator();

    MainModel *mainModel() const;

private:
    MachineCommsCoordinator *m_machineComms;
};
