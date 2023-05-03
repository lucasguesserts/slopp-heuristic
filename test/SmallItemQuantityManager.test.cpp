#include <catch2/catch_test_macros.hpp>

#include <vector>

#include <itertools.hpp>

#include "SmallItem.hpp"
#include "SmallItemQuantityManager.hpp"

using namespace packing;

TEST_CASE("small item hash", "[SmallItemHash]") {
    const auto small_items = std::vector<SmallItem>{
        {{1, 2, 3}},
        {{1, 2, 4}},
        {{1, 3, 3}},
        {{4, 2, 3}},
        {{1, 2, 3}}};
    const auto hash = SmallItemHash{};
    CHECK(hash(small_items[0]) != hash(small_items[1]));
    CHECK(hash(small_items[0]) != hash(small_items[2]));
    CHECK(hash(small_items[0]) != hash(small_items[3]));
    CHECK(hash(small_items[0]) == hash(small_items[4]));
}

TEST_CASE("small item quantity", "[SmallItemQuantityManager]") {
    const auto small_items = std::vector<SmallItem>{
        {{1, 2, 3}},
        {{1, 2, 4}},
        {{1, 3, 3}},
        {{4, 2, 3}},
    };
    const auto quantities = std::vector<Quantity>{
        3,
        4,
        8,
        1,
    };
    REQUIRE(small_items.size() == quantities.size());
    auto quantity_manager = SmallItemQuantityManager();
    for (auto && [small_item, quantity] : iter::zip(small_items, quantities)) {
        quantity_manager[small_item] = quantity;
    }
    for (auto && [small_item, quantity] : iter::zip(small_items, quantities)) {
        CHECK(quantity_manager[small_item] == quantity);
    }
}
