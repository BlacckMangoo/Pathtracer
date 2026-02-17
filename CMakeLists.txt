cmake_minimum_required(VERSION 4.0)
project(PathTracer)

set(CMAKE_CXX_STANDARD 20)

include_directories(${PROJECT_SOURCE_DIR}/include)
add_library(core
ppm.cpp primitives.cpp tracer.cpp modelFileParser.cpp )

add_executable(PathTracer main.cpp   )

target_link_libraries( PathTracer PRIVATE core  )
