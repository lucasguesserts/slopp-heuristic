#include <catch2/benchmark/catch_benchmark.hpp>
#include <catch2/catch_test_macros.hpp>

#include "fibonacci.hpp"

constexpr auto n = Value{34};

TEST_CASE("Fibonacci Benchmark", "[benchmark][factorial]") {
    BENCHMARK("fibonacci") {
        return fibonacci(n);
    };
}
