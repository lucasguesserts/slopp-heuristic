#include <catch2/catch_test_macros.hpp>

#include <vector>

#include <cppitertools/itertools.hpp>

#include "BoolCuboid.hpp"

using namespace packing;

TEST_CASE("constructor", "[BoolCuboid]") {
    const auto size_x = CoordinateType{2};
    const auto size_y = CoordinateType{3};
    const auto size_z = CoordinateType{5};
    const auto cuboid = BoolCuboid{{size_x, size_y, size_z}};
    for (auto&& [x, y, z] : iter::product(iter::range(size_x), iter::range(size_y), iter::range(size_z))) {
        CHECK_FALSE(cuboid.is_occupied(x, y, z));
    }
}

TEST_CASE("set position as occupied", "[BoolCuboid]") {
    const auto size_x = CoordinateType{5};
    const auto size_y = CoordinateType{7};
    const auto size_z = CoordinateType{11};
    auto cuboid = BoolCuboid{{size_x, size_y, size_z}};
    SECTION("occupy") {
        const auto initial_position = Vector3D{1, 1, 1};
        const auto final_position = Vector3D{3, 3, 3};
        cuboid.occupy(initial_position, final_position);
        SECTION("is occupied - position") {
            for (auto&& [x, y, z] : iter::product(iter::range(size_x), iter::range(size_y), iter::range(size_z))) {
                const auto within_x = initial_position.x() <= x && x < final_position.x();
                const auto within_y = initial_position.y() <= y && y < final_position.y();
                const auto within_z = initial_position.z() <= z && z < final_position.z();
                if (within_x && within_y && within_z) {
                    CHECK(cuboid.is_occupied(x, y, z));
                } else {
                    CHECK(cuboid.is_free(x, y, z));
                }
            }
        }
        SECTION("is_occcupied - range") {
            CHECK(cuboid.is_any_occupied(initial_position, final_position));
            CHECK_FALSE(cuboid.are_all_free(initial_position, final_position));
        }
    }
}
