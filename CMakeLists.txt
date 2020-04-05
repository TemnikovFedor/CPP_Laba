cmake_minimum_required(VERSION 3.15)
project(CPP_Laba)

set(CMAKE_CXX_STANDARD 11)

# error: missed configuration of compilation flags!
# you can see it in compile_commands.json if set this variable:
set(CMAKE_EXPORT_COMPILE_COMMANDS ON)


add_executable(CPP_Laba main.cpp Explicit.cpp Explicit.h Implicit.cpp Implicit.h)

# error: the linker stage is missed!
# without this stage you will not be able to use functional interface  (like omp_get_num_threads())
# and OpenMP directives will not work!
# basically you will use serial version of program
