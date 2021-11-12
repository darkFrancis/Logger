cmake_minimum_required(VERSION 3.21.2)
project(Logger VERSION 0.1)

find_package(Qt5Core REQUIRED)

set(SOURCES
    inc/Logger/Logger.hpp
    src/version.hpp
    src/Logger.cpp)
add_library(${PROJECT_NAME} ${SOURCES})
target_include_directories(${PROJECT_NAME} PUBLIC inc)
target_link_libraries(${PROJECT_NAME} Qt5::Core)
