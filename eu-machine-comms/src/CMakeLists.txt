# Copyright, Burkhard Stubert (burkhard.stubert@embeddeduse.com)

cmake_minimum_required(VERSION 3.19)

project(MachineComms VERSION 0.1 LANGUAGES CXX)

set(CMAKE_INCLUDE_CURRENT_DIR ON)

set(CMAKE_AUTOMOC ON)

set(CMAKE_CXX_STANDARD 17)
set(CMAKE_CXX_STANDARD_REQUIRED ON)

find_package(Qt6 COMPONENTS Core REQUIRED)

add_library(${PROJECT_NAME} SHARED
    engine_twin.cpp
    quantity.cpp

    can_bus_simulator.cpp
)

add_library(EmUse::MachineComms ALIAS ${PROJECT_NAME})

target_include_directories(${PROJECT_NAME}
    PUBLIC .)

target_link_libraries(${PROJECT_NAME}
  PRIVATE Qt6::Core)
