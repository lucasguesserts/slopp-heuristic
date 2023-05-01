#include <catch2/catch_test_macros.hpp>

#include "fibonacci.hpp"

TEST_CASE("fibonacci", "[fibonacci]") {
    REQUIRE(fibonacci(0) == 0);
    REQUIRE(fibonacci(1) == 1);
    REQUIRE(fibonacci(2) == 1);
    REQUIRE(fibonacci(3) == 2);
    REQUIRE(fibonacci(4) == 3);
    REQUIRE(fibonacci(5) == 5);
    REQUIRE(fibonacci(6) == 8);
    REQUIRE(fibonacci(7) == 13);
    REQUIRE(fibonacci(8) == 21);
    REQUIRE(fibonacci(9) == 34);
    REQUIRE(fibonacci(10) == 55);
    REQUIRE(fibonacci(11) == 89);
    REQUIRE(fibonacci(12) == 144);
    REQUIRE(fibonacci(13) == 233);
    REQUIRE(fibonacci(14) == 377);
    REQUIRE(fibonacci(15) == 610);
    REQUIRE(fibonacci(16) == 987);
    REQUIRE(fibonacci(17) == 1597);
    REQUIRE(fibonacci(18) == 2584);
    REQUIRE(fibonacci(19) == 4181);
    REQUIRE(fibonacci(20) == 6765);
}
