add_executable(tests
    file_test.cpp
    sequential_test.cpp
    test_helpers.cpp
    test_helpers.h
    luby_test.cpp
    jones_test.cpp
    load_graph_test.cpp
    largest_degree_first_test.cpp)

find_package(Catch2 3)

target_link_libraries(tests PRIVATE core)
target_link_libraries(tests PRIVATE Catch2::Catch2WithMain)

add_test(NAME tests COMMAND tests)

set(THREADS_PREFER_PTHREAD_FLAG ON)
find_package(Threads REQUIRED)
target_link_libraries(tests PRIVATE Threads::Threads)
