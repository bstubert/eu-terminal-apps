# Copyright, Burkhard Stubert (burkhard.stubert@embeddeduse.com)

cmake_minimum_required(VERSION 3.19)

project(test_main_view LANGUAGES CXX)

set(CMAKE_INCLUDE_CURRENT_DIR ON)
set(CMAKE_AUTOMOC ON)
set(CMAKE_AUTORCC ON)

set(CMAKE_CXX_STANDARD 17)
set(CMAKE_CXX_STANDARD_REQUIRED ON)

find_package(Qt6 COMPONENTS QuickTest REQUIRED)

qt_add_executable(${PROJECT_NAME}
    test_main_view.cpp
)

target_link_libraries(${PROJECT_NAME}
  PRIVATE Qt6::QuickTest)
