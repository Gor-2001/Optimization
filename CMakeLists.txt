cmake_minimum_required(VERSION 3.16)
project(optimization)

set(CMAKE_CXX_STANDARD 17)


include_directories(${CMAKE_CURRENT_SOURCE_DIR}/inc)

add_executable(optimization
    src/main.cpp
    src/prediction_sorted_vector.cpp
    inc/prediction_sorted_vector.h
)

