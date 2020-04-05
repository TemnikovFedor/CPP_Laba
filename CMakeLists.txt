cmake_minimum_required(VERSION 3.14)
project(CPP_Laba)

set(CMAKE_CXX_STANDARD 11)
set(CMAKE_EXPORT_COMPILE_COMMANDS ON)

find_package(OpenMP COMPONENTS CXX REQUIRED)

add_executable(CPP_Laba main.cpp Explicit.cpp Explicit.h Implicit.cpp Implicit.h)
target_link_libraries(CPP_Laba OpenMP::OpenMP_CXX)
