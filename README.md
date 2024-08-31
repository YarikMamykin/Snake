# SNAKE

## Description
Classic Snake implementation in C++

## Demo

![](./demo.gif)

## Dependencies
- C++17 - C++ standard used
- pthread - multithreading lib 
- Xlib - X11 graphical lib
- GTest - unit test framework (pulled internally by cmake)
- CMake - dependency and build manager (v 3.0 and higher)
- GCC - compiler (v 11.2)

## Installation
### Developer mode
- cmake -S . -B build -DCMAKE_BUILD_TYPE=Debug
- cmake --build build
- cmake --install build

### Release mode
- cmake -S . -B build -DCMAKE_BUILD_TYPE=Release
- cmake --build build
- sudo cmake --install build

For easier use `install.sh` script can be used.
After installation just run `Snake` command from your terminal and enjoy the game.
