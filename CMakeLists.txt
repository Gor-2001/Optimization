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
    src/window.cpp
    src/window.h
    src/define.h

    src/prediction/src/window.cpp
    src/prediction/src/test.cpp
    src/prediction/inc/window.h
    src/prediction/inc/test.h


    src/aaa/src/window.cpp
    src/aaa/src/test.cpp
    src/aaa/inc/window.h
    src/aaa/inc/test.h
)

target_link_libraries(optimization Qt5::Widgets)
