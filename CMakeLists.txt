cmake_minimum_required(VERSION 3.12)
project(linoodle)
enable_language(ASM)
find_package(Threads REQUIRED)

# Build PE parser library
option(BUILD_SHARED_LIBS "" OFF)
add_subdirectory(pe-parse)
set(BUILD_SHARED_LIBS ON)

# Build linoodle
add_library(oodle_26 linoodle.cpp windows_api.cpp windows_library.cpp)
target_link_libraries(oodle_26 PRIVATE pe-parse Threads::Threads)
target_compile_definitions(oodle_26 PRIVATE OODLE_26_API)

add_library(oodle_28 linoodle.cpp windows_api.cpp windows_library.cpp)
target_link_libraries(oodle_28 PRIVATE pe-parse Threads::Threads)
target_compile_definitions(oodle_28 PRIVATE OODLE_28_API)

# Build tester
add_executable(testlinoodle test/test.cpp)
target_link_libraries(testlinoodle PRIVATE Threads::Threads ${CMAKE_DL_LIBS})
