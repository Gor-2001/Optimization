# TODO: asm
# Assemble .asm file manually
# set(ASM_SOURCE_FILE ${CMAKE_CURRENT_SOURCE_DIR}/src/packaging/hello_asm.asm)
# set(ASM_OBJECT_FILE ${CMAKE_CURRENT_BINARY_DIR}/hello_asm.o)

# TODO: asm
# add_custom_command(
#     OUTPUT ${ASM_OBJECT_FILE}
#     COMMAND as --64 ${ASM_SOURCE_FILE} -o ${ASM_OBJECT_FILE}
#     DEPENDS ${ASM_SOURCE_FILE}
#     COMMENT "Assembling 64-bit x86 assembly function: ${ASM_SOURCE_FILE}"
# )

cmake_minimum_required(VERSION 3.16)
project(optimization LANGUAGES CXX)

set(CMAKE_CXX_STANDARD 17)
set(CMAKE_CXX_STANDARD_REQUIRED ON)

set(CMAKE_AUTOMOC ON)
set(CMAKE_AUTOUIC ON)
set(CMAKE_AUTORCC ON)

if (CMAKE_BUILD_TYPE STREQUAL "Debug")
    add_compile_definitions(__DEBUG)
endif()

# Try Qt6 first, fall back to Qt5
find_package(Qt6 COMPONENTS Widgets QUIET)
if (Qt6_FOUND)
    message(STATUS "Using Qt6")
    set(QT_LIB Qt6::Widgets)
else()
    find_package(Qt5 COMPONENTS Widgets REQUIRED)
    message(STATUS "Using Qt5")
    set(QT_LIB Qt5::Widgets)
endif()

# Include project headers
include_directories(${CMAKE_CURRENT_SOURCE_DIR}/inc)

# Define sources
add_executable(optimization
    src/main.cpp
    src/main_window.cpp src/main_window.h
    src/base_window.cpp src/base_window.h
    src/prediction/prediction_window.cpp src/prediction/prediction_window.h
    src/jump_table/jump_table_window.cpp src/jump_table/jump_table_window.h
    src/dependency/dependency_window.cpp src/dependency/dependency_window.h
    src/packaging/packaging_window.cpp src/packaging/packaging_window.h
)

# Link against Qt
target_link_libraries(optimization PRIVATE ${QT_LIB})

