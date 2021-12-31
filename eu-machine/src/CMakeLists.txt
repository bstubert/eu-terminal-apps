# Copyright, Burkhard Stubert (burkhard.stubert@embeddeduse.com)

cmake_minimum_required(VERSION 3.19)

project(Machine VERSION 0.1 LANGUAGES CXX)

set(CMAKE_INCLUDE_CURRENT_DIR ON)

set(CMAKE_AUTOMOC ON)

set(CMAKE_CXX_STANDARD 17)
set(CMAKE_CXX_STANDARD_REQUIRED ON)

find_package(Qt6 COMPONENTS Core SerialBus REQUIRED)

add_library(${PROJECT_NAME} SHARED
    engine_twin.cpp
    machine.cpp
    machine_creator.cpp
    quantity.cpp
    quantity_object.cpp
    private/can_bus_router.cpp
    private/can_bus_simulator.cpp
    private/engine_twin_impl.cpp
    private/mock_can_bus_device.cpp
    private/mock_machine.cpp
    private/simulator_machine.cpp
)

add_library(EmUse::Machine ALIAS ${PROJECT_NAME})

target_include_directories(${PROJECT_NAME}
    PUBLIC .)

target_link_libraries(${PROJECT_NAME}
  PRIVATE Qt6::Core Qt6::SerialBus)
