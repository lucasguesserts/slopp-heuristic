#include <catch2/catch_test_macros.hpp>

#include "BoolCuboid.hpp"

using namespace packing;

TEST_CASE("constructor", "[BoolCuboid]") {
    const auto size_x = SizeType{2};
    const auto size_y = SizeType{3};
    const auto size_z = SizeType{5};
    const auto cuboid = BoolCuboid{{size_x, size_y, size_z}};
    for (auto i = 0u; i < size_x; ++i) {
        for (auto j = 0u; j < size_y; ++j) {
            for (auto k = 0u; k < size_z; ++k) {
                CHECK_FALSE(cuboid(i, j, k));
            }
        }
    }
}

TEST_CASE("set position as occupied", "[BoolCuboid]") {
    const auto size_x = SizeType{2};
    const auto size_y = SizeType{3};
    const auto size_z = SizeType{5};
    auto cuboid = BoolCuboid{{size_x, size_y, size_z}};
    for (auto i = 0u; i < size_x; ++i) {
        for (auto j = 0u; j < size_y; ++j) {
            for (auto k = 0u; k < size_z; ++k) {
                cuboid.occupy(i, j, k);
            }
        }
    }
    for (auto i = 0u; i < size_x; ++i) {
        for (auto j = 0u; j < size_y; ++j) {
            for (auto k = 0u; k < size_z; ++k) {
                CHECK(cuboid(i, j, k));
            }
        }
    }
}
