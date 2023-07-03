#include "Test.hpp"

#include "AllocatedSmallItem.hpp"
#include "SmallItem.hpp"
#include "Surface.hpp"
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

TEST_CASE("surface", "[AllocatedSmallItem]") {
    // size
    const auto size_x = CoordinateType{2};
    const auto size_y = CoordinateType{3};
    const auto size_z = CoordinateType{5};
    const auto size = Vector3D{size_x, size_y, size_z};
    // position
    const auto position_x = CoordinateType{7};
    const auto position_y = CoordinateType{11};
    const auto position_z = CoordinateType{13};
    const auto position = Vector3D{position_x, position_y, position_z};
    // item
    const auto small_item = SmallItem{size};
    const auto allocated_small_item = AllocatedSmallItem{small_item, position};
    // expected surface
    const auto expected = Surface{
        {7, 11, 12},
        {7, 12, 12},
        {7, 13, 12},
        {8, 11, 12},
        {8, 12, 12},
        {8, 13, 12},
        {7, 11, 18},
        {7, 12, 18},
        {7, 13, 18},
        {8, 11, 18},
        {8, 12, 18},
        {8, 13, 18},
        {7, 10, 13},
        {7, 10, 14},
        {7, 10, 15},
        {7, 10, 16},
        {7, 10, 17},
        {8, 10, 13},
        {8, 10, 14},
        {8, 10, 15},
        {8, 10, 16},
        {8, 10, 17},
        {7, 14, 13},
        {7, 14, 14},
        {7, 14, 15},
        {7, 14, 16},
        {7, 14, 17},
        {8, 14, 13},
        {8, 14, 14},
        {8, 14, 15},
        {8, 14, 16},
        {8, 14, 17},
        {6, 11, 13},
        {6, 11, 14},
        {6, 11, 15},
        {6, 11, 16},
        {6, 11, 17},
        {6, 12, 13},
        {6, 12, 14},
        {6, 12, 15},
        {6, 12, 16},
        {6, 12, 17},
        {6, 13, 13},
        {6, 13, 14},
        {6, 13, 15},
        {6, 13, 16},
        {6, 13, 17},
        {9, 11, 13},
        {9, 11, 14},
        {9, 11, 15},
        {9, 11, 16},
        {9, 11, 17},
        {9, 12, 13},
        {9, 12, 14},
        {9, 12, 15},
        {9, 12, 16},
        {9, 12, 17},
        {9, 13, 13},
        {9, 13, 14},
        {9, 13, 15},
        {9, 13, 16},
        {9, 13, 17}};
    // check
    CHECK(allocated_small_item.surface() == expected);
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
