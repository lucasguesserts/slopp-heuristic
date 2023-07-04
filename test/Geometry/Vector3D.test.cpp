#include "Test.hpp"

#include "Geometry/Vector3D.hpp"
#include <catch2/catch_test_macros.hpp>

using namespace packing;

TEST_CASE("constructor", "[Vector3D]") {
    const auto x = CoordinateType{2};
    const auto y = CoordinateType{3};
    const auto z = CoordinateType{5};
    const auto vector3D = Vector3D{x, y, z};
    CHECK(vector3D.x() == x);
    CHECK(vector3D.y() == y);
    CHECK(vector3D.z() == z);
    CHECK(vector3D.volume() == 30);
}

TEST_CASE("equality", "[Vector3D]") {
    const auto x = CoordinateType{2};
    const auto y = CoordinateType{3};
    const auto z = CoordinateType{5};
    const auto vector3D = Vector3D{x, y, z};
    SECTION("true") {
        CHECK(vector3D == Vector3D{x, y, z});
    }
    SECTION("false") {
        CHECK_FALSE(vector3D == Vector3D{x + 1, y, z});
        CHECK_FALSE(vector3D == Vector3D{x, y + 1, z});
        CHECK_FALSE(vector3D == Vector3D{x, y, z + 1});
    }
}

TEST_CASE("sum", "[Vector3D]") {
    const auto x_lhs = CoordinateType{2};
    const auto y_lhs = CoordinateType{3};
    const auto z_lhs = CoordinateType{5};
    const auto lhs = Vector3D{x_lhs, y_lhs, z_lhs};
    const auto x_rhs = CoordinateType{7};
    const auto y_rhs = CoordinateType{11};
    const auto z_rhs = CoordinateType{13};
    const auto rhs = Vector3D{x_rhs, y_rhs, z_rhs};
    const auto expected = Vector3D{x_lhs + x_rhs, y_lhs + y_rhs, z_lhs + z_rhs};
    CHECK((lhs + rhs) == expected);
}

TEST_CASE("less", "[Vector3D]") {
    const auto x = CoordinateType{2};
    const auto y = CoordinateType{3};
    const auto z = CoordinateType{5};
    const auto v = Vector3D{x, y, z};
    SECTION("true") {
        CHECK(v < Vector3D{x + 1, y, z});
        CHECK(v < Vector3D{x, y + 1, z});
        CHECK(v < Vector3D{x, y, z + 1});
    }
    SECTION("false") {
        CHECK_FALSE((v < Vector3D{x, y, z}));
        CHECK_FALSE((v < Vector3D{x - 1, y, z}));
        CHECK_FALSE((v < Vector3D{x, y - 1, z}));
        CHECK_FALSE((v < Vector3D{x, y, z - 1}));
    }
}
