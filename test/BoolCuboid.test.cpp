#include <catch2/catch_test_macros.hpp>

#include "BoolCuboid.hpp"

using namespace packing;

TEST_CASE("constructor", "[BoolCuboid]") {
    const auto size_x = SizeType{2};
    const auto size_y = SizeType{3};
    const auto size_z = SizeType{5};
    const auto matrix = BoolCuboid{{size_x, size_y, size_z}};
    for (auto i = 0u; i < size_x; ++i) {
        for (auto j = 0u; j < size_y; ++j) {
            for (auto k = 0u; k < size_z; ++k) {
                CHECK_FALSE(matrix(i, j, k));
            }
        }
    }
}
