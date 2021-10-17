# Copyright, Burkhard Stubert (burkhard.stubert@embeddeduse.com)

cmake_minimum_required(VERSION 3.19)

project(test_main_view)

find_package(Qt6 COMPONENTS QuickTest REQUIRED)

qt_add_executable(${PROJECT_NAME}
    test_main_view.cpp
#    tst_qml.qrc
#    tst_main_view.qml
)


target_link_libraries(${PROJECT_NAME}
  PRIVATE Qt6::QuickTest)
