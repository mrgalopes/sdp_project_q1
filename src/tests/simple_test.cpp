#include <catch2/catch_test_macros.hpp>

int factorial(int number) {
    int result = 1;
    for (int i = 2; i <= number; i++) {
        result *= i;
    }
    return result;
}

TEST_CASE("should calculate factorials correctly", "[factorial]") {
    REQUIRE(factorial(1) == 1);
    REQUIRE(factorial(2) == 2);
    REQUIRE(factorial(3) == 6);
    REQUIRE(factorial(10) == 3628800);
}
