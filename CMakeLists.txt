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

    src/base_window.h
    src/base_window.cpp

    src/prediction/prediction_window.cpp
    src/prediction/prediction_window.h

    src/jump_table/jump_table_window.cpp
    src/jump_table/jump_table_window.h

    src/dependency/dependency_window.cpp
    src/dependency/dependency_window.h

    src/packaging/packaging_window.cpp
    src/packaging/packaging_window.h
)

target_link_libraries(optimization Qt5::Widgets)
