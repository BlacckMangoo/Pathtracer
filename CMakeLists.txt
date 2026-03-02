cmake_minimum_required(VERSION 3.2)

set(CMAKE_CXX_COMPILER clang++)
set(CMAKE_C_COMPILER clang)

project(PathTracer)
set(CMAKE_CXX_STANDARD 20)
set(CMAKE_EXPORT_COMPILE_COMMANDS ON)
include_directories(${PROJECT_SOURCE_DIR}/include)
add_library(core
ppm.cpp primitives.cpp tracer.cpp modelFileParser.cpp )

add_executable(PathTracer main.cpp   )

target_link_libraries( PathTracer PRIVATE core  )
