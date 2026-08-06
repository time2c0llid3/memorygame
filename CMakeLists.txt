cmake_minimum_required(VERSION 3.10)

project(MemoryGame)
aux_source_directory(src SOURCES)
add_executable(memexec ${SOURCES})

target_include_directories(memexec PRIVATE include)
find_package(SDL3 REQUIRED)
target_link_libraries(memexec PRIVATE SDL3)
target_compile_options(memexec PRIVATE -Wall)
