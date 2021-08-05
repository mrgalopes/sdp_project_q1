cmake_minimum_required(VERSION 3.20)
project(untitled)

set(CMAKE_CXX_STANDARD 20)


add_subdirectory(src)

add_subdirectory(externals)

# Include tests
add_subdirectory(tests)
