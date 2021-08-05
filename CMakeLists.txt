cmake_minimum_required(VERSION 3.20)
project(untitled)

set(CMAKE_CXX_STANDARD 20)

add_executable(debug src/main.cpp src/vertex.cpp src/vertex.h)

# Include tests
Include(FetchContent)

FetchContent_Declare(
        Catch2
        GIT_REPOSITORY https://github.com/catchorg/Catch2.git
        GIT_TAG        v3.0.0-preview3
)

FetchContent_MakeAvailable(Catch2)

add_executable(tests tests/simple_test.cpp)
target_link_libraries(tests PRIVATE Catch2::Catch2WithMain)
