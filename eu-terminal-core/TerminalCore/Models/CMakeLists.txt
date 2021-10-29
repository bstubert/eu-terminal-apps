# Copyright, Burkhard Stubert (burkhard.stubert@embeddeduse.com)

cmake_minimum_required(VERSION 3.19)

project(TerminalCoreModels VERSION 0.1 LANGUAGES CXX)

set(CMAKE_INCLUDE_CURRENT_DIR ON)

set(CMAKE_AUTOMOC ON)

set(CMAKE_CXX_STANDARD 17)
set(CMAKE_CXX_STANDARD_REQUIRED ON)

find_package(Qt6 COMPONENTS Core Qml REQUIRED)

qt6_add_library(${PROJECT_NAME} SHARED
)

qt6_add_qml_module(${PROJECT_NAME}
    URI TerminalCore.Models
    VERSION 0.1
    PLUGIN_TARGET QmlModuleTerminalCoreModels
    SOURCES
        main_model.cpp
        quantity_object.cpp
        business_logic_coordinator.cpp
        business_logic_singleton.cpp
)

add_library(EmUse::TerminalCoreModels ALIAS ${PROJECT_NAME})

target_include_directories(${PROJECT_NAME}
    PUBLIC .)

target_link_libraries(${PROJECT_NAME}
  PRIVATE Qt6::Core Qt6::Qml EmUse::MachineComms)
