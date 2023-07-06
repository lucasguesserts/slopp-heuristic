#include "Test/Test.hpp"

#include <vector>

#include "SmallItem/BasicSmallItem.hpp"
#include "SmallItem/Container/QuantityManager.hpp"

using namespace packing;

TEST_CASE("small item quantity", "[SmallItemQuantityManager]") {
    // This does not test the quantity manager's ability to handle
    // repeated small items, missing small items,
    // or small items with zero quantity.
    const auto small_items = std::vector<BasicSmallItem::Ptr>{
        std::make_shared<BasicSmallItem>(Vector3D{1, 2, 3}, 3),
        std::make_shared<BasicSmallItem>(Vector3D{1, 2, 4}, 4),
        std::make_shared<BasicSmallItem>(Vector3D{1, 3, 3}, 8),
        std::make_shared<BasicSmallItem>(Vector3D{4, 2, 3}, 1),
    };
    auto quantity_manager = QuantityManager<SmallItemType::Ptr, SmallItemType::Hash>();
    for (auto & small_item : small_items) {
        quantity_manager.add_item(small_item);
    }
    for (auto & small_item : small_items) {
        CHECK(quantity_manager.quantity(small_item) == small_item->quantity());
    }
    for (auto & small_item : small_items) {
        quantity_manager.remove_one_item(small_item);
    }
    for (auto & small_item : small_items) {
        CHECK(quantity_manager.quantity(small_item) == small_item->quantity() - 1);
    }
}
