#include <catch2/catch_test_macros.hpp>

#include "Vector3D.hpp"
#include "LargeObject.hpp"

using namespace packing;

TEST_CASE("constructor", "[LargeObject]") {
    const auto x = CoordinateType{1};
    const auto y = CoordinateType{2};
    const auto z = CoordinateType{3};
    const auto size = Vector3D{x, y, z};
    const auto item = LargeObject{size};
    CHECK(item.size().x() == x);
    CHECK(item.size().y() == y);
    CHECK(item.size().z() == z);
}
