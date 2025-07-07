cmake_minimum_required(VERSION 3.16)

project(Calculator VERSION 0.1 LANGUAGES CXX)

find_package(Qt6 REQUIRED COMPONENTS Core Quick Qml)

set(CMAKE_CXX_STANDARD_REQUIRED ON)
set(CMAKE_CXX_STANDARD 17)
set(CMAKE_CXX_STANDARD_REQUIRED ON)

qt_standard_project_setup(REQUIRES 6.8)

add_subdirectory(source)