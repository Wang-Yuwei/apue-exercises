cmake_minimum_required(VERSION 3.4.0)

set(CMAKE_CXX_STANDARD 14)

project(apue-solutions)

set(CMAKE_C_FLAGS "${CMAKE_C_FLAGS} -Wall -Wextra -Werror")
set(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} -Wall -Wextra -Werror")

add_subdirectory(chapter2)
add_subdirectory(chapter3)
