#include "Test.hpp"

#include "BoolCuboid.hpp"
#include "CornerPointIdentifier.hpp"
#include "Vector3D.hpp"

using namespace packing;

// All cases in which a point is a Corner Point are verified in this test.
// Not all cases in which a point is not a Corner Point are verified in this test.

TEST_CASE("case 1", "[CornerPointIdentifier]") {
    /**
    Cases covered:
    | case | x | y | z | covered in this test |
    |:----:|---|---|---|:--------------------:|
    | 0    | i | i | i | yes                  |
    | 1    | i | i | o | yes                  |
    | 2    | i | o | i | yes                  |
    | 3    | i | o | o | yes                  |
    | 4    | o | i | i | yes                  |
    | 5    | o | i | o | yes                  |
    | 6    | o | o | i | yes                  |
    | 7    | o | o | o | no                   |
    i: inexistent
    o: occupied
    */
    /**
    "small_items": [
        {
            "length": 1,
            "width": 1,
            "height": 1,
            "x": 1.0,
            "y": 0.0,
            "z": 0.0
        },
        {
            "length": 1,
            "width": 1,
            "height": 1,
            "x": 0.0,
            "y": 1.0,
            "z": 0.0
        },
        {
            "length": 1,
            "width": 1,
            "height": 1,
            "x": 0.0,
            "y": 0.0,
            "z": 1.0
        },
        {
            "length": 1,
            "width": 1,
            "height": 1,
            "x": 3.0,
            "y": 0.0,
            "z": 0.0
        }
    ]
    */
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

TEST_CASE("case 2", "[CornerPointIdentifier]") {
    /**
    Cases covered:
    | case | x | y | z | covered in this test |
    |:----:|---|---|---|:--------------------:|
    | 0    | i | i | i | no                   |
    | 1    | i | i | o | yes                  |
    | 2    | i | o | i | yes                  |
    | 3    | i | o | o | no                   |
    | 4    | o | i | i | yes                  |
    | 5    | o | i | o | no                   |
    | 6    | o | o | i | no                   |
    | 7    | o | o | o | yes                  |
    i: inexistent
    o: occupied
    */
    /**
    "small_items": [
        {
            "length": 1,
            "width": 2,
            "height": 2,
            "x": 0.0,
            "y": 0.0,
            "z": 0.0
        },
        {
            "length": 1,
            "width": 1,
            "height": 2,
            "x": 1.0,
            "y": 0.0,
            "z": 0.0
        },
        {
            "length": 1,
            "width": 1,
            "height": 1,
            "x": 1.0,
            "y": 1.0,
            "z": 0.0
        }
    ]
    */
    const auto x_size = CoordinateType{3};
    const auto y_size = CoordinateType{4};
    const auto z_size = CoordinateType{5};
    auto space = BoolCuboid({x_size, y_size, z_size});
    space.occupy({0, 0, 0}, {1, 2, 2});
    space.occupy({1, 0, 0}, {2, 1, 2});
    space.occupy({1, 1, 0}, {2, 2, 1});
    const auto corner_point_identifier = CornerPointIdentifier(space);
    SECTION("corner point") {
        CHECK(corner_point_identifier.is_corner_point({2, 0, 0}));
        CHECK(corner_point_identifier.is_corner_point({0, 2, 0}));
        CHECK(corner_point_identifier.is_corner_point({0, 0, 2}));
        CHECK(corner_point_identifier.is_corner_point({1, 1, 1}));
    }
    SECTION("NOT corner point") {
        CHECK_FALSE(corner_point_identifier.is_corner_point({0, 0, 0}));
        CHECK_FALSE(corner_point_identifier.is_corner_point({1, 0, 0}));
        CHECK_FALSE(corner_point_identifier.is_corner_point({2, 2, 0}));
        CHECK_FALSE(corner_point_identifier.is_corner_point({2, 1, 0}));
    }
}
