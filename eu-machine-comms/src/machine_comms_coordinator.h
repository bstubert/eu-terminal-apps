// Copyright, Burkhard Stubert (burkhard.stubert@embeddeduse.com)

#pragma once

#include <memory>

class EngineTwin;

class MachineCommsCoordinator
{
public:
    MachineCommsCoordinator();
    MachineCommsCoordinator(const MachineCommsCoordinator &) = delete;
    MachineCommsCoordinator &operator=(const MachineCommsCoordinator &) = delete;
    ~MachineCommsCoordinator();

    EngineTwin *engine() const;

private:
    struct Impl;
    std::unique_ptr<Impl> m_impl;
};
