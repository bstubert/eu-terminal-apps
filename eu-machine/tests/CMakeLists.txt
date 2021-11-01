# Copyright, Burkhard Stubert (burkhard.stubert@embeddeduse.com)

cmake_minimum_required(VERSION 3.19)

project(eu-machine-comms-tests)

include(CTest)
add_subdirectory(can_bus_device)
add_subdirectory(can_bus_router)
add_subdirectory(engine_twin)

