cmake_minimum_required(VERSION 3.15)
project(part3 C)

set(CMAKE_C_STANDARD 99)

add_executable(part3 main.c 3a.c)
target_link_libraries(part3 pthread)