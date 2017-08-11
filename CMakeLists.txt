cmake_minimum_required(VERSION 3.6)
project(alvey_explorer)

set(CMAKE_CXX_STANDARD 11)


set(SOURCE_FILES)

add_subdirectory(dependencies)
add_subdirectory(explorer)
add_subdirectory(projects)

add_executable(alvey_explorer ${SOURCE_FILES})

target_include_directories(alvey_explorer PUBLIC dependencies projects)
target_compile_options(alvey_explorer PUBLIC -O0)