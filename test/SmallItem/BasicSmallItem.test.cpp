#include "Test/Test.hpp"

#include "SmallItem/Specialization/BasicSmallItem.hpp"

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

TEST_CASE("hash", "[BasicSmallItem]") {
    const auto small_items = std::vector<BasicSmallItem::Ptr>{
        std::make_shared<BasicSmallItem>(Vector3D{1, 2, 3}, 1),
        std::make_shared<BasicSmallItem>(Vector3D{1, 2, 4}, 1),
        std::make_shared<BasicSmallItem>(Vector3D{1, 3, 3}, 1),
        std::make_shared<BasicSmallItem>(Vector3D{4, 2, 3}, 1),
        std::make_shared<BasicSmallItem>(Vector3D{1, 2, 3}, 2),
        std::make_shared<BasicSmallItem>(Vector3D{1, 2, 3}, 1)};
    const auto hash = SmallItemType::Hash{};
    CHECK(hash(small_items[0]) != hash(small_items[1]));
    CHECK(hash(small_items[0]) != hash(small_items[2]));
    CHECK(hash(small_items[0]) != hash(small_items[3]));
    CHECK(hash(small_items[0]) != hash(small_items[4]));
    CHECK(hash(small_items[0]) == hash(small_items[5]));
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
