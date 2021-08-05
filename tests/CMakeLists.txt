add_executable(tests
    simple_test.cpp
)
target_link_libraries(tests PRIVATE Catch2::Catch2WithMain)