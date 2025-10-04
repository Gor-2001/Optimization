cmake_minimum_required(VERSION 3.16)
project(optimization)

set(CMAKE_CXX_STANDARD 17)
set(CMAKE_AUTOMOC ON)
set(CMAKE_AUTORCC ON)
#set(CMAKE_AUTOUIC ON)

find_package(Qt5 REQUIRED COMPONENTS Widgets)

include_directories(${CMAKE_CURRENT_SOURCE_DIR}/inc)

add_executable(optimization

    src/main.cpp
    src/main_window.cpp
    src/main_window.h
    src/main_utils.h

    src/prediction/src/prediction_window.cpp
    src/prediction/src/prediction_test.cpp
    src/prediction/inc/prediction_window.h
    src/prediction/inc/prediction_test.h

    src/packaging/src/packaging_window.cpp
    src/packaging/src/packaging_test.cpp
    src/packaging/inc/packaging_window.h
    src/packaging/inc/packaging_test.h

    src/jump_table/src/jump_table_window.cpp
    src/jump_table/src/jump_table_test.cpp
    src/jump_table/inc/jump_table_window.h
    src/jump_table/inc/jump_table_test.h

    src/info/info_window.h
    src/info/info_window.cpp
)

target_link_libraries(optimization Qt5::Widgets)
