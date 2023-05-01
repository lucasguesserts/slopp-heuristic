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
    const auto size_x = SizeType{5};
    const auto size_y = SizeType{7};
    const auto size_z = SizeType{11};
    auto cuboid = BoolCuboid{{size_x, size_y, size_z}};
    SECTION("occupy space") {
        const auto initial_position = Size{1, 1, 1};
        const auto final_position = Size{2, 2, 2};
        cuboid.occupy(initial_position, final_position);
        for (auto x = 0u; x < size_x; ++x) {
            for (auto y = 0u; y < size_y; ++y) {
                for (auto z = 0u; z < size_z; ++z) {
                    const auto within_x = initial_position.x() <= x && x < final_position.x();
                    const auto within_y = initial_position.y() <= y && y < final_position.y();
                    const auto within_z = initial_position.z() <= z && z < final_position.z();
                    if (within_x && within_y && within_z) {
                        CHECK(cuboid(x, y, z));
                    } else {
                        CHECK_FALSE(cuboid(x, y, z));
                    }
                }
            }
        }
    }
}
