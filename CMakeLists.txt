cmake_minimum_required(VERSION 3.16)
project(optimization)

set(CMAKE_CXX_STANDARD 17)
set(CMAKE_AUTOMOC ON)
set(CMAKE_AUTORCC ON)

find_package(Qt5 REQUIRED COMPONENTS Widgets)
include_directories(${CMAKE_CURRENT_SOURCE_DIR}/inc)

# Assemble .asm file manually
set(ASM_SOURCE_FILE ${CMAKE_CURRENT_SOURCE_DIR}/src/packaging/hello_asm.asm)
set(ASM_OBJECT_FILE ${CMAKE_CURRENT_BINARY_DIR}/hello_asm.o)

add_custom_command(
    OUTPUT ${ASM_OBJECT_FILE}
    COMMAND as --64 ${ASM_SOURCE_FILE} -o ${ASM_OBJECT_FILE}
    DEPENDS ${ASM_SOURCE_FILE}
    COMMENT "Assembling 64-bit x86 assembly function: ${ASM_SOURCE_FILE}"
)


add_executable(optimization
    ${ASM_OBJECT_FILE}
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
