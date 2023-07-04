#include "Test/Test.hpp"

#include "SmallItem/BasicSmallItem.hpp"

#include "Geometry/Vector3D.hpp"

using namespace packing;

TEST_CASE("constructor", "[BasicSmallItem]") {
    const auto x = CoordinateType{1};
    const auto y = CoordinateType{2};
    const auto z = CoordinateType{3};
    const auto measurement = Vector3D{x, y, z};
    const auto quantity = Quantity{4};
    const auto item = BasicSmallItem{measurement, quantity};
    CHECK(item.measurement().x() == x);
    CHECK(item.measurement().y() == y);
    CHECK(item.measurement().z() == z);
    CHECK(item.quantity() == quantity);
}

TEST_CASE("equality operator", "[BasicSmallItem]") {
    const auto item = BasicSmallItem{{1, 2, 3}, 4};
    SECTION("equal") {
        const auto other = BasicSmallItem{{1, 2, 3}, 4};
        CHECK(item == other);
    }
    SECTION("not equal") {
        const auto other = BasicSmallItem{{2, 2, 3}, 4};
        CHECK(!(item == other));
    }
    SECTION("not equal") {
        const auto other = BasicSmallItem{{1, 2, 3}, 5};
        CHECK(!(item == other));
    }
}
