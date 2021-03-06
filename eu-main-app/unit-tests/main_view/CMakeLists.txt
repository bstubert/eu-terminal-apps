# Copyright, Burkhard Stubert (burkhard.stubert@embeddeduse.com)

cmake_minimum_required(VERSION 3.19)

project(test_main_view LANGUAGES CXX)

set(CMAKE_INCLUDE_CURRENT_DIR ON)
set(CMAKE_AUTOMOC ON)
set(CMAKE_AUTORCC ON)

set(CMAKE_CXX_STANDARD 17)
set(CMAKE_CXX_STANDARD_REQUIRED ON)

find_package(Qt6 COMPONENTS Quick QuickTest REQUIRED)

add_executable(${PROJECT_NAME}
    test_main_view.cpp
)

set_source_files_properties(
    ../../src/MainView.qml PROPERTIES QT_RESOURCE_ALIAS MainView.qml
)

qt_add_qml_module(${PROJECT_NAME}
    URI EmUse.Tests.MainView
    VERSION 0.1
    QML_FILES tst_main_view.qml ../../src/MainView.qml
)

target_link_libraries(${PROJECT_NAME}
  PRIVATE Qt6::Quick Qt6::QuickTest EmUse::BusinessLogicModels)
