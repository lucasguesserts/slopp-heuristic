#include <catch2/catch_test_macros.hpp>

#include "AllocatedSmallItem.hpp"
#include "SmallItem.hpp"
#include "Vector3D.hpp"

using namespace packing;

TEST_CASE("constructor", "[AllocatedSmallItem]") {
    // size
    const auto size_x = CoordinateType{1};
    const auto size_y = CoordinateType{2};
    const auto size_z = CoordinateType{3};
    const auto size = Vector3D{size_x, size_y, size_z};
    // position
    const auto position_x = CoordinateType{4};
    const auto position_y = CoordinateType{5};
    const auto position_z = CoordinateType{6};
    const auto position = Vector3D{4, 5, 6};
    // item
    const auto small_item = SmallItem{size};
    const auto allocated_small_item = AllocatedSmallItem{small_item, position};
    // check
    CHECK(allocated_small_item.size().x() == size_x);
    CHECK(allocated_small_item.size().y() == size_y);
    CHECK(allocated_small_item.size().z() == size_z);
    CHECK(allocated_small_item.position().x() == position_x);
    CHECK(allocated_small_item.position().y() == position_y);
    CHECK(allocated_small_item.position().z() == position_z);
}

TEST_CASE("equality operator", "[SmallItem]") {
    const auto item = AllocatedSmallItem{{{1, 2, 3}}, {4, 5, 6}};
    SECTION("equal") {
        const auto other = AllocatedSmallItem{{{1, 2, 3}}, {4, 5, 6}};
        CHECK(item == other);
    }
    SECTION("not equal") {
        const auto other = AllocatedSmallItem{{{100, 2, 3}}, {4, 5, 6}};
        CHECK_FALSE((item == other));
    }
    SECTION("not equal") {
        const auto other = AllocatedSmallItem{{{1, 2, 3}}, {100, 5, 6}};
        CHECK_FALSE((item == other));
    }
}
