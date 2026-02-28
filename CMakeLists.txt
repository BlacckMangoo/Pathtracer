cmake_minimum_required(VERSION 3.2)
project(PathTracer)

set(CMAKE_CXX_STANDARD 20)

include_directories(${PROJECT_SOURCE_DIR}/include)
add_library(core
ppm.cpp primitives.cpp tracer.cpp modelFileParser.cpp )

add_executable(PathTracer main.cpp   )

target_link_libraries( PathTracer PRIVATE core  )
target_compile_definitions(core PUBLIC
    PROJECT_ROOT="${PROJECT_SOURCE_DIR}"
)


