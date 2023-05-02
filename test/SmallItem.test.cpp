#include <catch2/catch_test_macros.hpp>

#include "SmallItem.hpp"
#include "Vector3D.hpp"

using namespace packing;

TEST_CASE("constructor", "[SmallItem]") {
    const auto x = CoordinateType{1};
    const auto y = CoordinateType{2};
    const auto z = CoordinateType{3};
    const auto size = Vector3D{x, y, z};
    const auto item = SmallItem{size};
    CHECK(item.size().x() == x);
    CHECK(item.size().y() == y);
    CHECK(item.size().z() == z);
}

TEST_CASE("equality operator", "[SmallItem]") {
    const auto item = SmallItem{{1, 2, 3}};
    SECTION("equal") {
        const auto other = SmallItem{{1, 2, 3}};
        CHECK(item == other);
    }
    SECTION("not equal") {
        const auto other = SmallItem{{2, 2, 3}};
        CHECK(!(item == other));
    }
}
