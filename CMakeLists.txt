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
    src/prediction_sorted_vector.cpp
    inc/main_window.h
    inc/prediction_sorted_vector.h
)

target_link_libraries(optimization Qt5::Widgets)
