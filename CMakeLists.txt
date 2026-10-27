cmake_minimum_required(VERSION 3.14)
project(OwnGame C CXX)

set(CMAKE_CXX_STANDARD 17)
set(CMAKE_CXX_STANDARD_REQUIRED ON)

if(MSVC)
    add_compile_options(/utf-8)
endif()

include_directories(include)

file(GLOB SOURCES "src/*.cpp" "src/*.c")

add_executable(OwnGame main.cpp ${SOURCES})

add_custom_command(
    TARGET OwnGame PRE_BUILD
    COMMAND ${CMAKE_COMMAND} -E rm -f "${CMAKE_CURRENT_BINARY_DIR}/game_data.db"
    COMMENT "Очистка старого файла базы данных game_data.db перед новой сборкой..."
)