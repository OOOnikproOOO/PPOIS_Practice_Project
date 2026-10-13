cmake_minimum_required(VERSION 3.10)
project(OwnGame C CXX)

set(CMAKE_CXX_STANDARD 17)
set(CMAKE_CXX_STANDARD_REQUIRED ON)

if(MSVC)
    add_compile_options(/utf-8)
endif()

include_directories(include)

file(GLOB SOURCES "src/*.cpp" "src/*.c")

add_executable(OwnGame main.cpp ${SOURCES})