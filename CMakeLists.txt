cmake_minimum_required(VERSION 3.21.2)
project(Logger VERSION 0.3)

find_package(Qt5Core REQUIRED)

set(SOURCES
    inc/Logger/Logger.hpp
    src/version.hpp
    src/Logger.cpp)
add_library(${PROJECT_NAME} SHARED ${SOURCES})
target_include_directories(${PROJECT_NAME} PUBLIC inc)
target_link_libraries(${PROJECT_NAME} Qt5::Core)
target_compile_definitions(${PROJECT_NAME} PUBLIC _BUILD_LOGGER_LIB)
if(NOT DEFINED_VERSION)
    target_compile_definitions(${PROJECT_NAME} PUBLIC DEFINED_VERSION="${PROJECT_VERSION}")
endif()
