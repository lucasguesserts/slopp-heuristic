#include "Test.hpp"

#include "BoolCuboid.hpp"
#include "CornerPointIdentifier.hpp"
#include "Vector3D.hpp"

using namespace packing;

TEST_CASE("identify corner points", "[CornerPointIdentifier]") {
    // create a bool cuboid and occupy some of its spaces
    const auto x_size = CoordinateType{3};
    const auto y_size = CoordinateType{4};
    const auto z_size = CoordinateType{5};
    auto space = BoolCuboid({x_size, y_size, z_size});
    space.occupy({1, 0, 0}, {2, 1, 1});
    space.occupy({0, 1, 0}, {1, 2, 1});
    space.occupy({0, 0, 1}, {1, 1, 2});
    const auto corner_point_identifier = CornerPointIdentifier(space);
    SECTION("corner point") {
        CHECK(corner_point_identifier.is_corner_point({0, 0, 0}));
        CHECK(corner_point_identifier.is_corner_point({2, 0, 0}));
        CHECK(corner_point_identifier.is_corner_point({0, 2, 0}));
        CHECK(corner_point_identifier.is_corner_point({0, 0, 2}));
    }
    SECTION("NOT corner point") {
        CHECK_FALSE(corner_point_identifier.is_corner_point({2, 3, 4}));
        CHECK_FALSE(corner_point_identifier.is_corner_point({1, 0, 0}));
        CHECK_FALSE(corner_point_identifier.is_corner_point({2, 2, 2}));
    }
}
