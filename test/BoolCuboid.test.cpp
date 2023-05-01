#include <catch2/catch_test_macros.hpp>

#include <cppitertools/itertools.hpp>
#include <cppitertools/product.hpp>
#include <cppitertools/range.hpp>

#include "BoolCuboid.hpp"

using namespace packing;

TEST_CASE("constructor", "[BoolCuboid]") {
    const auto size_x = SizeType{2};
    const auto size_y = SizeType{3};
    const auto size_z = SizeType{5};
    const auto cuboid = BoolCuboid{{size_x, size_y, size_z}};
    for (auto&& [x, y, z] : iter::product(iter::range(size_x), iter::range(size_y), iter::range(size_z))) {
        CHECK_FALSE(cuboid(x, y, z));
    }
}

TEST_CASE("set position as occupied", "[BoolCuboid]") {
    const auto size_x = SizeType{5};
    const auto size_y = SizeType{7};
    const auto size_z = SizeType{11};
    auto cuboid = BoolCuboid{{size_x, size_y, size_z}};
    SECTION("occupy space") {
        const auto initial_position = Size{1, 1, 1};
        const auto final_position = Size{3, 3, 3};
        cuboid.occupy(initial_position, final_position);
        for (auto&& [x, y, z] : iter::product(iter::range(size_x), iter::range(size_y), iter::range(size_z))) {
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
