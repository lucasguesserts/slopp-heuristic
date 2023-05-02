#include <catch2/catch_test_macros.hpp>

#include "LargeObject.hpp"
#include "Vector3D.hpp"

using namespace packing;

TEST_CASE("constructor", "[LargeObject]") {
    const auto x = CoordinateType{1};
    const auto y = CoordinateType{2};
    const auto z = CoordinateType{3};
    const auto size = Vector3D{x, y, z};
    const auto large_object = LargeObject{size};
    CHECK(large_object.size().x() == x);
    CHECK(large_object.size().y() == y);
    CHECK(large_object.size().z() == z);
}
