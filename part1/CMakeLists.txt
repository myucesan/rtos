cmake_minimum_required(VERSION 3.15)
project(part1 C)

set(CMAKE_C_STANDARD 99)

add_executable(part1 main.c 1a.c 1b.c 1c.c)
target_link_libraries(part1 pthread)
