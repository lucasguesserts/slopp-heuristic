#include <catch2/benchmark/catch_benchmark.hpp>
#include <catch2/catch_test_macros.hpp>

#include "SmallItem.hpp"

TEST_CASE("SmallItem Benchmark", "[benchmark][SmallItem]") {
    BENCHMARK("null") {
        return 1;
    };
}
