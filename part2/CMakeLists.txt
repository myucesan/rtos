cmake_minimum_required(VERSION 3.15)
project(part2 C)

set(CMAKE_C_STANDARD 99)

add_executable(part2 main.c 2a.c)
target_link_libraries(part2 pthread)
target_link_libraries(part2 rt)