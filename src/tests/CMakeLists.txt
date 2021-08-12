add_executable(tests
    simple_test.cpp
    file_test.cpp
    sequential_test.cpp test_helpers.cpp test_helpers.h luby_test.cpp)
target_link_libraries(tests PRIVATE core)
target_link_libraries(tests PRIVATE Catch2::Catch2WithMain)

add_test(NAME tests COMMAND tests)
