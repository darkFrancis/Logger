cmake_minimum_required(VERSION 3.21.2)
project(Logger VERSION 0.4)

execute_process(COMMAND conan install ${CMAKE_SOURCE_DIR})
include(${CMAKE_BINARY_DIR}/conanbuildinfo.cmake)
conan_basic_setup()
find_file(QtCmake common-qt.cmake)
include(${QtCmake})

set_qt5_modules(Core)

set(SOURCES
    inc/Logger/Logger.hpp
    src/version.hpp
    src/Logger.cpp)
add_qt_bin(SHARED
    NAME ${PROJECT_NAME}
    SOURCES ${SOURCES}
    INCLUDES inc)
set_common_defines()
target_compile_definitions(${PROJECT_NAME} PUBLIC _BUILD_LOGGER_LIB)
