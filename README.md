# Optimization

A C++/Qt application for studying algorithm performance and optimization techniques. Built with CMake for Linux systems.

## Overview

This educational tool provides interactive demonstrations of various algorithms and their optimizations, allowing users to observe CPU behavior and performance characteristics in real-time.

## Features

- Multiple algorithm test modules with dedicated windows
- Information panels displaying algorithm descriptions from external text files
- Configurable runtime parameters via spin box controls
- Qt Widgets-based cross-platform GUI
- Performance comparison and visualization

## Technical Stack

- C++17 or later
- Qt5 (Widgets module)
- CMake 3.x build system
- Linux target platform

## Building

### Prerequisites

Install the required development tools and libraries:
```bash
sudo apt update
sudo apt install build-essential cmake qtbase5-dev
```

Note: The `qt5-default` package is deprecated in recent Ubuntu versions. Use `qtbase5-dev` instead.

### Build Instructions

1. Configure the build system:
```bash
cmake -S . -B out
```

2. Compile the project:
```bash
cmake --build out
```

3. Run the application:
```bash
./out/optimization
```

## Usage

Launch the application and select an algorithm module from the main window. Adjust parameters using the provided controls and execute tests to observe performance metrics.

## Project Goals

This project serves as an educational resource for:
- Understanding algorithmic complexity in practice
- Observing the impact of optimizations on runtime performance
- Exploring CPU behavior under different workloads
- Learning performance analysis techniques

## Platform Support

Currently tested and supported on Linux. While Qt provides cross-platform capabilities, this project has only been validated on Linux distributions.
