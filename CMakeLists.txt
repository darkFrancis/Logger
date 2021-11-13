cmake_minimum_required(VERSION 3.21.2)
project(Logger VERSION 0.3)

if(NOT EXISTS ${CMAKE_BINARY_DIR}/conanbuildinfo.cmake)
    execute_process(COMMAND conan install ${CMAKE_SOURCE_DIR} --build=missing)
endif()
include(${CMAKE_BINARY_DIR}/conanbuildinfo.cmake)
conan_basic_setup()
include(${CONAN_COMMONQTCMAKE_ROOT}/common-qt.cmake)

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
