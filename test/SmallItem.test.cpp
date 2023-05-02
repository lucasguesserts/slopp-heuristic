#include <catch2/catch_test_macros.hpp>

#include "Size.hpp"
#include "SmallItem.hpp"

using namespace packing;

TEST_CASE("constructor", "[SmallItem]") {
    const auto x = SizeType{1};
    const auto y = SizeType{2};
    const auto z = SizeType{3};
    const auto size = Size{x, y, z};
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
