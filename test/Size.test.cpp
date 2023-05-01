#include <catch2/catch_test_macros.hpp>

#include "Size.hpp"

using namespace packing;

TEST_CASE("constructor", "[Size]") {
    const auto x = SizeType{2};
    const auto y = SizeType{3};
    const auto z = SizeType{5};
    const auto size = Size{x, y, z};
    CHECK(size.x() == x);
    CHECK(size.y() == y);
    CHECK(size.z() == z);
    CHECK(size.volume() == 30);
}
