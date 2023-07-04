#include "Test.hpp"

#include "SmallItem.hpp"
#include "Geometry/Surface.hpp"
#include "Geometry/Vector3D.hpp"

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

TEST_CASE("surface", "[AllocatedSmallItem]") {
    // size
    const auto size_x = CoordinateType{2};
    const auto size_y = CoordinateType{3};
    const auto size_z = CoordinateType{5};
    const auto size = Vector3D{size_x, size_y, size_z};
    // item
    const auto small_item = SmallItem{size};
    // expected surface
    const auto expected = Surface{
        {0, 0, -1},
        {0, 1, -1},
        {0, 2, -1},
        {1, 0, -1},
        {1, 1, -1},
        {1, 2, -1},
        {0, 0, 5},
        {0, 1, 5},
        {0, 2, 5},
        {1, 0, 5},
        {1, 1, 5},
        {1, 2, 5},
        {0, -1, 0},
        {0, -1, 1},
        {0, -1, 2},
        {0, -1, 3},
        {0, -1, 4},
        {1, -1, 0},
        {1, -1, 1},
        {1, -1, 2},
        {1, -1, 3},
        {1, -1, 4},
        {0, 3, 0},
        {0, 3, 1},
        {0, 3, 2},
        {0, 3, 3},
        {0, 3, 4},
        {1, 3, 0},
        {1, 3, 1},
        {1, 3, 2},
        {1, 3, 3},
        {1, 3, 4},
        {-1, 0, 0},
        {-1, 0, 1},
        {-1, 0, 2},
        {-1, 0, 3},
        {-1, 0, 4},
        {-1, 1, 0},
        {-1, 1, 1},
        {-1, 1, 2},
        {-1, 1, 3},
        {-1, 1, 4},
        {-1, 2, 0},
        {-1, 2, 1},
        {-1, 2, 2},
        {-1, 2, 3},
        {-1, 2, 4},
        {2, 0, 0},
        {2, 0, 1},
        {2, 0, 2},
        {2, 0, 3},
        {2, 0, 4},
        {2, 1, 0},
        {2, 1, 1},
        {2, 1, 2},
        {2, 1, 3},
        {2, 1, 4},
        {2, 2, 0},
        {2, 2, 1},
        {2, 2, 2},
        {2, 2, 3},
        {2, 2, 4}};
    // check
    CHECK(small_item.surface() == expected);
}
