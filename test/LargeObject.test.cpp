#include <catch2/catch_test_macros.hpp>

#include "Size.hpp"
#include "LargeObject.hpp"

using namespace packing;

TEST_CASE("constructor", "[LargeObject]") {
    const auto x = SizeType{1};
    const auto y = SizeType{2};
    const auto z = SizeType{3};
    const auto size = Size{x, y, z};
    const auto item = LargeObject{size};
    CHECK(item.size().x() == x);
    CHECK(item.size().y() == y);
    CHECK(item.size().z() == z);
}
