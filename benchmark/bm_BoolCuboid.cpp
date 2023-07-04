#include "Test/Test.hpp"
#include <catch2/benchmark/catch_benchmark.hpp>

#include "SmallItem.hpp"

#include <vector>

TEST_CASE("SmallItem Benchmark", "[benchmark][SmallItem]") {
    /**
    This benchmark is to decide which implementation is going to be used:
        - vector<vector<vector<bool>>> ; access[i][j][k];
        - vector<bool> ; multiplication[i + (j * size_x) + (k * size_x * size_y)];
    If both yield the same result, choose the first.
    If not, use the best one.
    */

    using std::vector;

    const unsigned size_x = 100;
    const unsigned size_y = 100;
    const unsigned size_z = 100;
    const vector<vector<vector<bool>>> access(size_x, vector<vector<bool>>(size_y, vector<bool>(size_z, false)));
    const vector<bool> multiplication(size_x * size_y * size_z, false);

    BENCHMARK("access") {
        auto ret = bool{false};
        for (auto i = 0u; i < size_x; ++i)
            for (auto j = 0u; j < size_y; ++j)
                for (auto k = 0u; k < size_z; ++k)
                    ret &= access[i][j][k];
        return ret;
    };

    BENCHMARK("multiplication") {
        auto ret = bool{false};
        for (auto i = 0u; i < size_x; ++i)
            for (auto j = 0u; j < size_y; ++j)
                for (auto k = 0u; k < size_z; ++k)
                    ret &= multiplication[i + (j * size_x) + (k * size_x * size_y)];
        return ret;
    };
}
