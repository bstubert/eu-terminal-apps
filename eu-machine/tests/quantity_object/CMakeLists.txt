# Copyright, Burkhard Stubert (burkhard.stubert@embeddeduse.com)

cmake_minimum_required(VERSION 3.19)

project(test_quantity_object LANGUAGES CXX)

set(CMAKE_INCLUDE_CURRENT_DIR ON)

set(CMAKE_AUTOMOC ON)

set(CMAKE_CXX_STANDARD 17)
set(CMAKE_CXX_STANDARD_REQUIRED ON)

find_package(Qt6 COMPONENTS Core Test REQUIRED)

add_executable(${PROJECT_NAME}
    test_quantity_object.cpp
    ../../src/quantity_object.cpp
)

add_test(
    NAME ${PROJECT_NAME}
    COMMAND ${PROJECT_NAME}
)

target_include_directories(${PROJECT_NAME}
    PRIVATE
        ../../src
)

target_link_libraries(${PROJECT_NAME}
  PRIVATE Qt6::Core Qt6::Test)

