cmake_minimum_required(VERSION 3.14)
project(OwnGame C CXX)

set(CMAKE_CXX_STANDARD 17)
set(CMAKE_CXX_STANDARD_REQUIRED ON)

if(MSVC)
    add_compile_options(/utf-8)
endif()

include_directories(include)

file(GLOB SOURCES "src/*.cpp" "src/*.c")

add_library(OwnGameCore STATIC ${SOURCES})
if(WIN32)
    target_link_libraries(OwnGameCore PUBLIC winmm)
endif()

add_executable(OwnGame main.cpp)
target_link_libraries(OwnGame PRIVATE OwnGameCore)

add_custom_command(
    TARGET OwnGame PRE_BUILD
    COMMAND ${CMAKE_COMMAND} -E rm -f "${CMAKE_CURRENT_BINARY_DIR}/game_data.db"
    COMMENT "Cleaning up the old game_data.db database file before a new build..."
)

add_custom_command(
    TARGET OwnGame POST_BUILD
    COMMAND ${CMAKE_COMMAND} -E copy_directory "${CMAKE_CURRENT_SOURCE_DIR}/assets" "$<TARGET_FILE_DIR:OwnGame>/assets"
    COMMENT "Copying 'assets' next to the executable file..."
)

include(FetchContent)
FetchContent_Declare(
    googletest
    URL https://github.com/google/googletest/archive/refs/tags/v1.14.0.zip
)

set(gtest_force_shared_crt ON CACHE BOOL "" FORCE)
FetchContent_MakeAvailable(googletest)

enable_testing()

add_executable(UnitTests tests/tests.cpp)
target_link_libraries(UnitTests PRIVATE OwnGameCore GTest::gtest_main)

include(GoogleTest)
gtest_discover_tests(UnitTests)