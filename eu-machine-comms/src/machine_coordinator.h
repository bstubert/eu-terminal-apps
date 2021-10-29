// Copyright, Burkhard Stubert (burkhard.stubert@embeddeduse.com)

#pragma once

#include <memory>

class EngineTwin;

class MachineCoordinator
{
public:
    MachineCoordinator();
    MachineCoordinator(const MachineCoordinator &) = delete;
    MachineCoordinator &operator=(const MachineCoordinator &) = delete;
    ~MachineCoordinator();

    EngineTwin *engine() const;

private:
    struct Impl;
    std::unique_ptr<Impl> m_impl;
};
