#include "Test.hpp"

#include "Vector3D.hpp"
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
    SECTION("equal") {
        const auto other = Vector3D{x, y, z};
        CHECK(vector3D == other);
    }
    SECTION("not equal") {
        const auto other = Vector3D{x + 1, y, z};
        CHECK(!(vector3D == other));
    }
    SECTION("not equal") {
        const auto other = Vector3D{x, y + 1, z};
        CHECK(!(vector3D == other));
    }
    SECTION("not equal") {
        const auto other = Vector3D{x, y, z + 1};
        CHECK(!(vector3D == other));
    }
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
